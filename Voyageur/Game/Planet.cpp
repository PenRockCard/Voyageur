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
        mineableResources.push_back(new Resource(resourceTemplates.at(nextResource)->getHardness(), (rand() % 1000),
                                                 resourceTemplates.at(nextResource)->getName()));
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

vector<Resource *> Planet::GetCurrentResources() {
    return mineableResources;
}

unsigned long long Planet::GetID() {
    return ID;
}

vector<Person> Planet::GetPeople() {
    vector<Person> peopleList;

    peopleList = people->getPeoplePlanet(ID);

    return peopleList;
}


