#pragma once

#include <iostream>
#include <vector>
#include "Resource.h"
#include "Person.h"
#include "People.h"

using namespace std;

class Planet {

    People *people;
    unsigned long long ID;
    vector<Resource *> minerableResources;

public:

    int *temperature = new int;

    void mineResources();

    unsigned long long GetID();

    vector<Resource *> GetCurrentResources();

    string *name = new string;

    Planet(string nameConstructor, People *peopleConstructor, unsigned long long planetIDConstructor);

    vector<Person> GetPeople();
};

