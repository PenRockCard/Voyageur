#include "Planet.h"

//Constructor.
//To be made more programatic later.

Planet::Planet(string nameConstructor, People *peopleConstructor,unsigned long long planetIDConstructor) {

    ID=planetIDConstructor;

    people=peopleConstructor;

    /*Resource tempResource = ;*/
    mineableResources.push_back(new Resource(1, 100, "Bronze"));
    mineableResources.push_back(new Resource(2, 76, "Iron"));
    mineableResources.push_back(new Resource(3, 50, "Steel"));
    mineableResources.push_back(new Resource(4, 40, "Mithril"));
    mineableResources.push_back(new Resource(5, 30, "Addy"));
    mineableResources.push_back(new Resource(6, 15, "Rune"));
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


