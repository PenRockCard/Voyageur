#pragma once

#include <string>

using namespace std;

class Resource {
public:
    string *name = new string;
    float *hardness = new float;
    float *amount = new float;

    Resource(float hardnessConstructor, float amountConstructor, string nameConstructor);

    //Resource();
    void mineResource();
};

