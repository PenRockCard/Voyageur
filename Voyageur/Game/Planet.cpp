#include "Planet.h"

//Constructor.
//To be made more programatic later.

Planet::Planet(string nameConstructor, People *peopleConstructor,unsigned long long planetIDConstructor) {

    ID=planetIDConstructor;

    people=peopleConstructor;

    /*Resource tempResource = ;*/
    minerableResources.push_back(new Resource(1, 100, "Bronze"));
    minerableResources.push_back(new Resource(2, 76, "Iron"));
    minerableResources.push_back(new Resource(3, 50, "Steel"));
    minerableResources.push_back(new Resource(4, 40, "Mithril"));
    minerableResources.push_back(new Resource(5, 30, "Addy"));
    minerableResources.push_back(new Resource(6, 15, "Rune"));
    *name = nameConstructor;

    for (int i = 0; i < 100; i++) {
        people->AddPerson(planetIDConstructor);
    }

}

void Planet::mineResources() {
    //current resource mining is new amount = current amount - 2/hardness
    for (Resource *planetResource: minerableResources) {
        planetResource->mineResource();
    }
}

vector<Resource *> Planet::GetCurrentResources() {
    return vector<Resource *>();
}

unsigned long long Planet::GetID() {
    return ID;
}

vector<Person> Planet::GetPeople() {
    vector<Person> peopleList;

    peopleList = people->getPeoplePlanet(ID);

    return peopleList;
}


