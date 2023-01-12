#pragma once

#include <iostream>
#include <vector>
#include "Resource.h"
#include "Person.h"

using namespace std;

class Planet {

    vector<Person *> population;

public:
    vector<Resource *> resources;
    int *temperature = new int;

    void mineResources();

    vector<Resource *> GetCurrentResources();

    string *name = new string;

    Planet(string nameConstructor);
};

