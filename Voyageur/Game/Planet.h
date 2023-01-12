#pragma once

#include <iostream>
#include <vector>
#include "Resource.h"

using namespace std;

class Planet {

public:
    vector<Resource *> resources;
    int *temperature = new int;

    void mineResources();

    vector<Resource *> GetCurrentResources();

    string *name = new string;

    Planet(string nameConstructor);
};

