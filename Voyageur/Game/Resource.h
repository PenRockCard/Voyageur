#pragma once

#include <string>

using namespace std;

class Resource {

    string *name = new string;
    float *hardness = new float;
    float *amount = new float;
    int *templateID = new int;

public:

    string GetName();

    float GetHardness();

    float GetAmount();

    Resource(float hardnessConstructor, float amountConstructor, string nameConstructor, int templateIDConstructor);

    //Resource();
    float mineResource();

    void updateAmount(float amountAdd);
};

