#include "Resource.h"
#include <iostream>

Resource::Resource(float hardnessConstructor, float amountConstructor, string nameConstructor,
                   int templateIDConstructor, bool infiniteConstructor) {
    *hardness = hardnessConstructor;
    *amount = amountConstructor;
    *name = nameConstructor;
    *templateID = templateIDConstructor;
    *infinite=infiniteConstructor;
}

/**
 * Any number of ways of doing this. Currently it's set up to take (1/20,000)*(1/hardness) of the resource.
 * Can be easily changed as needed
 * If infinite resources is enabled, it'll mine 1/10 the amount it'd take normally
 * @return
 */
float Resource::mineResource() {

    if (*this->amount <= 0) {
        if (infinite) {
            auto amtReturn2 = (float(1 / (10 * 200 * *hardness)));
            return amtReturn2;
        }
        return 0;
    }

    auto amtBefore = *this->amount;

    //Needs to be cast as a float to multiply as a float correctly.
    *this->amount = *amount - (float(1 / (200 * *hardness)));

    //Having a cout here speeds up the whole program, no idea why.
    //TODO: Figure out why.
//    cout << amtAfter;

    auto amtAfter = *this->amount;
    //If the amount would go below 0, this ensures it won't
    //TODO: This doesn't quite return the right amount.
    //More info: The stored resources amount is slightly different than the amount a resource began with when fully depleted.
    //IE: If it started with 8, it'll have like 8.00000053. Not sure where the bug originates from.
    if (*this->amount < 0) {

        *this->amount = 0;

        return amtBefore;
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

    *amount += amountAdd;

    if (*amount < 0) {
        *amount = 0;
    }

}

Resource::Resource(Resource *pResource) {
    *hardness = pResource->GetHardness();
    *amount = pResource->GetAmount();
    *name = pResource->GetName();
}



