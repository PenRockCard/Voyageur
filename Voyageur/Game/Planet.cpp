#include "Planet.h"

//Constructor.
//To be made more programatic later.

Planet::Planet(string nameConstructor, People *peopleConstructor,unsigned long long IDConstructor) {

    ID=IDConstructor;

    people=peopleConstructor;

    /*Resource tempResource = ;*/
    resources.push_back(new Resource(1, 100, "Bronze"));
    resources.push_back(new Resource(2, 76, "Iron"));
    resources.push_back(new Resource(3, 50, "Steel"));
    resources.push_back(new Resource(4, 40, "Mithril"));
    resources.push_back(new Resource(5, 30, "Addy"));
    resources.push_back(new Resource(6, 15, "Rune"));
    *name = nameConstructor;

    for (int i = 0; i < 100; i++) {
        people->AddPerson();
    }

}

void Planet::mineResources() {
    //current resource mining is new amount = current amount - 2/hardness
    for (Resource *planetResource: resources) {
        planetResource->mineResource();
    }
}

vector<Resource *> Planet::GetCurrentResources() {
    return vector<Resource *>();
}

unsigned long long Planet::GetID() {
    return ID;
}


