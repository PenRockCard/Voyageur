#pragma once
#include <algorithm>
#include "Planet.h"

//Constructor.
//To be made more programmatic later.

Planet::Planet(string nameConstructor, People *peopleConstructor, unsigned long long planetIDConstructor,
                   vector<ResourceTemplate *> resourceTemplates, double orbitLong, double orbitShort, int orbitPoints) {

    ID = planetIDConstructor;

    people = peopleConstructor;

    //Variables to quickly adjust resources for testing purposes.
    int numberResources = 10;
    int resourceAmount = 10;
    for (int i = 0; i < numberResources; i++) {

        int nextResource = rand() % resourceTemplates.size();

        //Checks if it's already on the planet.
        //If so, it just adds more to the planet, otherwise it adds it to the hashtable and creates a whole new resource
        if (resourceLocationTable.find(resourceTemplates.at(nextResource)->getID()) != resourceLocationTable.end()) {
            auto resourceLocation = resourceLocationTable.at(resourceTemplates.at(nextResource)->getID());
            mineableResources[resourceLocation]->updateAmount((rand() % resourceAmount));
        } else {
            //creates a new resource, and adds it to the minerals vector for the planet
            mineableResources.push_back(
                    new Resource(resourceTemplates.at(nextResource)->getHardness(), (rand() % resourceAmount),
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
    planetOrbit = new EllipseFunction(orbitLong, orbitShort,orbitPoints);
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



