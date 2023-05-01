#pragma once

#include <algorithm>
#include <iomanip>
#include "Planet.h"

//Constructor.
//To be made more programmatic later.

Planet::Planet(string nameConstructor, People *peopleConstructor, unsigned long long planetIDConstructor,
               vector<ResourceTemplate *> resourceTemplates, double orbitLong, double orbitShort, int orbitPoints,
               int orbitalCharacteristicPoints, double planetMass, int *timePerTickConstructor, double orbitOffSetX,
               double orbitOffSetY,
               double orbitAngle) {

    timePerTick = timePerTickConstructor;
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
    totalSeconds = 0;

    for (double angle = 0; angle < (2 * numbers::pi - angleIncrement); angle += angleIncrement) {
        PlanetOrbitalCharacteristics currentOrbitalPoint;
        currentOrbitalPoint.angle = angle;

        //For speed, the distance from the center (r), mu (from above), and a (from the ellipse equation) are needed.
        //Distance from center/the sun is based on the angle in polar co-ordinates
        //Based on the first equation (at time of writing) here: https://en.wikipedia.org/wiki/Ellipse#Polar_forms.
        //Could swap to use e instead of sin and square that result
        double rDistance = (planetOrbit->a * planetOrbit->b) /
                           sqrt(pow(planetOrbit->b * cos(angle), 2) + pow(planetOrbit->a * sin(angle), 2));
        currentOrbitalPoint.distanceFromOrbitCenter = rDistance;
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
        double time = (double) distance / velocity;
        currentOrbitalPoint.time = time; //Time in seconds between points
        totalSeconds += time;
        orbitalCharacteristics.push_back(currentOrbitalPoint);
        i++;
    }
    totalSeconds += orbitalCharacteristics[0].time; //Gets the final 2 points, maybe not needed?
    //The current angle (and therefore position) defaults to 0, that can be fixed
    currentAngle = 0;
    orbitalCharacteristicsPosition = 0;
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

/**
 * Updates the planets location.
 * Looks at the current angle and previous point (orbitalCharacteristicsPosition)
 * Then it looks at the time it'll take to get to the next position (in the orbitalCharacteristics vector).
 * 3 Cases:
 *      - Doesn't reach the next orbitalCharacteristics point (0)
 *          - Uses the current point and the next one to interpolate where it'll be
 *      - Gets to the next orbitalCharacteristics point, but doesn't go beyond that (1)
 *          - Uses the next point and the one beyond that to interpolate where it'll be
 *      - Goes beyond the next orbitalCharacteristics point (2+)
 *          - Checks when it'll not go beyond the next point and interpolates where it'll be
 * Loop around to find the current point based on the time
 */
void Planet::UpdateLocation() {

    //Finds the current time and velocity
    //Needed to cover case for when the position exceeds the number of elements in the vector
    int nextOrbitalCharacteristicsPosition = (((orbitalCharacteristicsPosition + 1) >= orbitalCharacteristics.size())
                                              ? 0 : (orbitalCharacteristicsPosition + 1));

    double t1 = orbitalCharacteristics[orbitalCharacteristicsPosition].time;
    double t2 = orbitalCharacteristics[nextOrbitalCharacteristicsPosition].time;
    double angle1 = orbitalCharacteristics[orbitalCharacteristicsPosition].angle;
    double angle2 = orbitalCharacteristics[nextOrbitalCharacteristicsPosition].angle;
    double velocity1 = orbitalCharacteristics[orbitalCharacteristicsPosition].velocity;
    double velocity2 = orbitalCharacteristics[nextOrbitalCharacteristicsPosition].velocity;
    double distance1 = orbitalCharacteristics[orbitalCharacteristicsPosition].distance;
    double distance2 = orbitalCharacteristics[nextOrbitalCharacteristicsPosition].distance;
    double currentTime = (t1 - t2) * (currentAngle - angle2) / (angle1 - angle2) + t2;
    double currentVelocity = (velocity1 - velocity2) * (currentAngle - angle2) / (angle1 - angle2) + velocity2;
    //The distance it starts at before adding the distance it travels over x time.
    double currentDistance = (distance2) * (1 - ((angle2 - currentAngle) / (angle2 - angle1))); //changed d1 to d2 here

    double distanceToTravel = *timePerTick * currentVelocity;

    if (ID>=0) {
        auto das =5;
    }

    //Case 1, doesn't pass any points
    if ((distanceToTravel + currentDistance) <= distance2) {
        double oldAngle = currentAngle;
        currentAngle =
                (angle1 - angle2) * (distanceToTravel + currentDistance) / (distance2) + angle2;
        //Case for when it goes over a full circle (2 pi)
        double angleDiff = currentAngle-oldAngle;
        if (currentAngle >= 2 * numbers::pi) {
            currentAngle -= numbers::pi;
        }

        cout << angleDiff << " Id: " << ID << endl;
    } else {
        //The 2 orbital characteristic points surrounding the current location
        int nextOrbitalCharacteristicsPosition3 = (((nextOrbitalCharacteristicsPosition + 1) >=
                                                    orbitalCharacteristics.size())
                                                   ? 0 : (nextOrbitalCharacteristicsPosition + 1));
        int nextOrbitalCharacteristicsPosition2 = nextOrbitalCharacteristicsPosition;

        //The time it takes to get to where it is
        double currentTime = (distance2 - currentDistance) / currentVelocity;
        double timeRemaining = *timePerTick - currentTime;
        while (true) {
            //distance2 = orbitalCharacteristics[nextOrbitalCharacteristicsPosition2].distance;
            velocity2 = orbitalCharacteristics[nextOrbitalCharacteristicsPosition2].velocity;

            double distanceTravelled2 = timeRemaining * velocity2;
            //Find new distance (distance3)
            double distance3 = orbitalCharacteristics[nextOrbitalCharacteristicsPosition3].distance;
            if (distance3 >= distanceTravelled2) {
                currentDistance = distanceTravelled2;
                break;
            }
            nextOrbitalCharacteristicsPosition2 = nextOrbitalCharacteristicsPosition3;
            nextOrbitalCharacteristicsPosition3 = (((nextOrbitalCharacteristicsPosition3 + 1) >=
                                                    orbitalCharacteristics.size())
                                                   ? 0 : (nextOrbitalCharacteristicsPosition3 + 1));
            //currentVelocity = velocity2;
            timeRemaining -= distance3 / velocity2;
        }
        angle1 = orbitalCharacteristics[nextOrbitalCharacteristicsPosition2].angle;
        angle2 = orbitalCharacteristics[nextOrbitalCharacteristicsPosition3].angle;

        distance1 = orbitalCharacteristics[nextOrbitalCharacteristicsPosition2].distance;
        distance2 = orbitalCharacteristics[nextOrbitalCharacteristicsPosition3].distance;
        double oldAngle = currentAngle;
        currentAngle =
                (angle1 - angle2) * (currentDistance) / (distance2) + angle2;
        //Case for when it goes over a full circle (2 pi)
        double angleDiff = currentAngle-oldAngle;
        if (currentAngle >= 2 * numbers::pi) {
            currentAngle -= numbers::pi;
        }
        orbitalCharacteristicsPosition= nextOrbitalCharacteristicsPosition2;

        cout << angleDiff << " Id: " << ID << endl;
    }
}

unsigned long long Planet::GetID() {
    return ID;
}

vector<Person> Planet::GetPeople() {
    vector<Person> peopleList;

    peopleList = people->getPeoplePlanet(ID);

    return peopleList;
}

PlanetOrbitalCharacteristics Planet::GetOrbitCharacteristicAt(int position) {
    return orbitalCharacteristics.at(position);
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

double Planet::GetCurrentAngle() {
    return currentAngle;
}

int Planet::GetOrbitalCharacteristicsSize() {
    return orbitalCharacteristics.size();
}





