#include "Resource.h"
#include <iostream>

Resource::Resource(float hardnessConstructor, float amountConstructor, string nameConstructor,
                   int templateIDConstructor) {
    *hardness = hardnessConstructor;
    *amount = amountConstructor;
    *name = nameConstructor;
    *templateID = templateIDConstructor;
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

    return amtBefore - amtAfter;

}

int Resource::GetTemplateID() {
    return *templateID;
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

void Resource::updateAmount(float amountAdd) {

    *amount+=amountAdd;

    if (*amount<0) {
        *amount=0;
    }

}

Resource::Resource(Resource *pResource) {
    *hardness = pResource->GetHardness();
    *amount = pResource->GetAmount();
    *name = pResource->GetName();
}



