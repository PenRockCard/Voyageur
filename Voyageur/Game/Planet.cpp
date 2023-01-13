#include <algorithm>
#include "Planet.h"

//Constructor.
//To be made more programatic later.

Planet::Planet(string nameConstructor, People *peopleConstructor, unsigned long long planetIDConstructor,
               vector<ResourceTemplate *> resourceTemplates) {

    ID = planetIDConstructor;

    people = peopleConstructor;

    int numberResources = 20;
    for (int i = 0; i < numberResources; i++) {

        int nextResource = rand() % resourceTemplates.size();

        if (resourceLocationTable.find(resourceTemplates.at(nextResource)->getID()) != resourceLocationTable.end()) {
            auto resourceLocation = resourceLocationTable.at(resourceTemplates.at(nextResource)->getID());
            mineableResources[resourceLocation]->updateAmount((rand() % 1000));
        } else {
            mineableResources.push_back(new Resource(resourceTemplates.at(nextResource)->getHardness(), (rand() % 1000),
                                                     resourceTemplates.at(nextResource)->getName(),
                                                     resourceTemplates.at(nextResource)->getID()));
            resourceLocationTable[resourceTemplates.at(nextResource)->getID()] = mineableResources.size() - 1;
        }
    }

    *name = nameConstructor;

    for (int i = 0; i < 100; i++) {
        people->AddPerson(planetIDConstructor);
    }

}

void Planet::mineResources() {
    //current resource mining is new amount = current amount - 2/hardness
    for (Resource *planetResource: mineableResources) {
        planetResource->mineResource();
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



