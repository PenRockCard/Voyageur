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
    void AddPerson();
    People();

};


#endif //VOYAGEUR_PEOPLE_H
