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

    unsigned long long id;

public:
    string GetName();

    Person(unsigned long long newId);

};


#endif //VOYAGEUR_PERSON_H
