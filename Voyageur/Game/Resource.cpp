#include "Resource.h"
#include <iostream>

Resource::Resource(float hardnessConstructor, float amountConstructor, string nameConstructor) {
    *hardness = hardnessConstructor;
    *amount = amountConstructor;
    *name = nameConstructor;
}

float Resource::mineResource() {

    if (*this->amount < 0) {
        return 0;
    }

    auto amtBefore = *this->amount;

    *this->amount = *amount - 2 / *hardness;

    auto amtAfter = *this->amount;
    if (*this->amount < 0) {

        auto amtReturned = *this->amount;

        *this->amount = 0;

        return amtReturned;
    }

    return amtBefore-amtAfter;

}

string Resource::GetName() {
    return *name;
}

float Resource::GetHardness() {
    return *hardness;
}

float Resource::GetAmount() {
    return *amount;
}

//Resource::Resource()
//{
//}


