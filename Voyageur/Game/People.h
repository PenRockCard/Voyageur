//
// Created by Chris on 2023-01-12.
//

#ifndef VOYAGEUR_PEOPLE_H
#define VOYAGEUR_PEOPLE_H


#include <vector>
#include "Person.h"

class People {

    vector<Person *> peopleList;
    unsigned long long nextID;

public:

    unsigned long long GetNextID();
    void AddPerson(unsigned long long PlanetID);
    People();

    vector<Person> getPeoplePlanet(unsigned long long int planetID);

    bool DeletePerson(unsigned long long int personID);

    unsigned long long int findPersonID(unsigned long long int personID);
};


#endif //VOYAGEUR_PEOPLE_H
