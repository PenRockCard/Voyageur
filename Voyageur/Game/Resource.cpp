#include "Resource.h"
#include <iostream>

Resource::Resource(float hardnessConstructor, float amountConstructor, string nameConstructor) {
    *hardness = hardnessConstructor;
    *amount = amountConstructor;
    *name = nameConstructor;
}

void Resource::mineResource() {

    *this->amount = *amount - 2 / *hardness;

}

//Resource::Resource()
//{
//}


