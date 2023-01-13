//
// Created by Chris on 2023-01-11.
//

#ifndef VOYAGEUR_PERSON_H
#define VOYAGEUR_PERSON_H

#include <iostream>

using namespace std;


class Person {

    string name;

    string *GetPeopleListTemp();

    unsigned long long ID;

    unsigned long long planetID;

public:
    string GetName();

    Person(unsigned long long newId, unsigned long long planetIDConstruct);

    unsigned long long int GetPlanet();

    unsigned long long int GetID();
};


#endif //VOYAGEUR_PERSON_H
