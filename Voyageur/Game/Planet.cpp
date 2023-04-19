#pragma once

#include <algorithm>
#include "Planet.h"

//Constructor.
//To be made more programmatic later.

Planet::Planet(string nameConstructor, People *peopleConstructor, unsigned long long planetIDConstructor,
               vector<ResourceTemplate *> resourceTemplates, double orbitLong, double orbitShort, int orbitPoints,
               int orbitalCharacteristicPoints, double planetMass, int *timePerTickConstructor, double orbitOffSetX, double orbitOffSetY,
               double orbitAngle) {

    timePerTick=timePerTickConstructor;
    ID = planetIDConstructor;

    people = peopleConstructor;

    //Variables to quickly adjust resources for testing purposes.
    int numberResources = 10;
    int resourceAmount = 10;
    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.
    uniform_int_distribution<> distNextResource(0,
                                                resourceTemplates.size() - 1); // distribute results between the min/max
    uniform_real_distribution<> resourceAmountDistribution(0, resourceAmount);
    for (int i = 0; i < numberResources; i++) {
        int nextResource = distNextResource(gen);
        //Checks if it's already on the planet.
        //If so, it just adds more to the planet, otherwise it adds it to the hashtable and creates a whole new resource
        if (resourceLocationTable.find(resourceTemplates.at(nextResource)->getID()) != resourceLocationTable.end()) {
            auto resourceLocation = resourceLocationTable.at(resourceTemplates.at(nextResource)->getID());
            mineableResources[resourceLocation]->updateAmount(resourceAmountDistribution(gen));
        } else {
            //creates a new resource, and adds it to the minerals vector for the planet
            mineableResources.push_back(
                    new Resource(resourceTemplates.at(nextResource)->getHardness(), resourceAmountDistribution(gen),
                                 resourceTemplates.at(nextResource)->getName(),
                                 resourceTemplates.at(nextResource)->getID()));
            //adds it to the hashtable
            resourceLocationTable[resourceTemplates.at(nextResource)->getID()] = mineableResources.size() - 1;
            //adds the currently stored resources on a planet, at the same location as the minerals vector
            //This allows for it to be easily found based on the hashtable above.
            storedResources.push_back(new Resource(resourceTemplates.at(nextResource)->getHardness(), 0,
                                                   resourceTemplates.at(nextResource)->getName(),
                                                   resourceTemplates.at(nextResource)->getID(), true));
        }
    }

    *name = nameConstructor;

    for (int i = 0; i < 100; i++) {
        people->AddPerson(planetIDConstructor);
    }

    //Sets up the planets orbit
    planetOrbit = new EllipseFunction(orbitLong, orbitShort, orbitPoints, orbitOffSetX, orbitOffSetY, orbitAngle);

    //Sets up the orbitalCharacteristics vector with a loop from 0 to 2*pi
    double angleIncrement = (2 * numbers::pi) / orbitalCharacteristicPoints;
    //Will need to add case for when a planet isn't orbiting the sun.
    //Standard gravitational parameter: https://en.wikipedia.org/wiki/Standard_gravitational_parameter
    double mu = (planetMass + SUN_MASS) * //Planet mass is in kg
                GRAVITATIONAL_CONSTANT; //Gravitational constant is in m^3/(kg*s^2)
    //Edge case for the last point? Should it be (< ... - angleIncrement) ?
    int i = 0;
    totalSeconds=0;

    for (double angle = 0; angle < (2 * numbers::pi - angleIncrement); angle += angleIncrement) {
        PlanetOrbitalCharacteristics currentOrbitalPoint;
        currentOrbitalPoint.angle = angle;

        //For speed, the distance from the center (r), mu (from above), and a (from the ellipse equation) are needed.
        //Distance from center/the sun is based on the angle in polar co-ordinates
        //Based on the first equation (at time of writing) here: https://en.wikipedia.org/wiki/Ellipse#Polar_forms.
        //Could swap to use e instead of sin and square that result
        double rDistance = (planetOrbit->a * planetOrbit->b) /
                           sqrt(pow(planetOrbit->b * cos(angle), 2) + pow(planetOrbit->a * sin(angle), 2));
        //Instant orbit speed: https://en.wikipedia.org/wiki/Orbital_speed#Instantaneous_orbital_speed
        double velocity = sqrt(mu * ((2 / rDistance) - (1 / planetOrbit->a))); //Velocity is in m/s
        currentOrbitalPoint.velocity = velocity;

        //Get time/distance
        //Finds the distance of the previous point, based on the current angle minus the difference
        double r0 = (planetOrbit->a * planetOrbit->b) /
                    sqrt(pow(planetOrbit->b * cos(angle - angleIncrement), 2) +
                           pow(planetOrbit->a * sin(angle - angleIncrement), 2));
        //Finds the distance between points using the cosine law
        double distance = sqrt(pow(rDistance, 2) + pow(r0, 2) - 2 * r0 * rDistance * cos(angleIncrement));
        currentOrbitalPoint.distance = distance; //Distance in m

        /* The time here is not totally accurate, Earth will have 31335714 seconds per year with this calculation,
         * however, Earth actually has 31536000 seconds per year, so a difference of ~0.635%
         */
        int time = (double)distance / velocity;
        currentOrbitalPoint.time = time; //Time in seconds between points
        totalSeconds+=time;
        orbitalCharacteristics.push_back(currentOrbitalPoint);
        i++;
    }
    totalSeconds+= orbitalCharacteristics[0].time; //Gets the final 2 points, maybe not needed?
    //The current angle (and therefore position) defaults to 0, that can be fixed
    currentAngle=0;
    orbitalCharacteristicPoints=0;
}

void Planet::mineResources() {
    //current resource mining is new amount = current amount - 2/hardness
    for (Resource *planetResource: mineableResources) {
        auto amt = planetResource->mineResource();
        storedResources.at(resourceLocationTable.at(planetResource->GetTemplateID()))->updateAmount(amt);
    }
}

/**
 * Need to add iterators and stuff for this...
 * @param order 0 or leave blank for unordered, 1 for order by name, 2 for order by amount, 3 for order by hardness
 * @return ordered list of resources
 */
vector<Resource *> Planet::GetCurrentResources(int order = RESOURCE_ORDER_NONE) {
    auto resourcesOrdered = mineableResources;
    switch (order) {
        case RESOURCE_ORDER_NONE:
            return mineableResources;
            break;
        case RESOURCE_ORDER_NAME:
            sort(resourcesOrdered.begin(), resourcesOrdered.end(), compareResourceName);
            break;
        case RESOURCE_ORDER_AMOUNT:
            sort(resourcesOrdered.begin(), resourcesOrdered.end(), compareResourceAmount);
            break;
        case RESOURCE_ORDER_HARDNESS:
            sort(resourcesOrdered.begin(), resourcesOrdered.end(), compareResourceHardness);
            break;
    }
    return resourcesOrdered;
}

vector<Resource *> Planet::GetStoredResources(int order = RESOURCE_ORDER_NONE) {
    auto resourcesOrdered = storedResources;
    switch (order) {
        case RESOURCE_ORDER_NONE:
            return storedResources;
            break;
        case RESOURCE_ORDER_NAME:
            sort(resourcesOrdered.begin(), resourcesOrdered.end(), compareResourceName);
            break;
        case RESOURCE_ORDER_AMOUNT:
            sort(resourcesOrdered.begin(), resourcesOrdered.end(), compareResourceAmount);
            break;
        case RESOURCE_ORDER_HARDNESS:
            sort(resourcesOrdered.begin(), resourcesOrdered.end(), compareResourceHardness);
            break;
    }
    return resourcesOrdered;
}

void Planet::UpdateLocation() {

}

unsigned long long Planet::GetID() {
    return ID;
}

vector<Person> Planet::GetPeople() {
    vector<Person> peopleList;

    peopleList = people->getPeoplePlanet(ID);

    return peopleList;
}

bool Planet::compareResourceAmount(Resource r1, Resource r2) {
    return (r1.GetAmount() < r2.GetAmount());
}

bool Planet::compareResourceName(Resource r1, Resource r2) {
    return (r1.GetName() < r2.GetName());
}

bool Planet::compareResourceHardness(Resource r1, Resource r2) {
    return (r1.GetHardness() < r2.GetHardness());
}



