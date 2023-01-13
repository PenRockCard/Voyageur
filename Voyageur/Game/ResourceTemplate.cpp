//
// Created by Chris on 2023-01-13.
//

#include "ResourceTemplate.h"

ResourceTemplate::ResourceTemplate(string name, float hardness, int ID) {

    resourceName = name;
    resourceHardness = hardness;
    resourceID = ID;

}

string ResourceTemplate::getName() {
    return resourceName;
}

float ResourceTemplate::getHardness() {
    return resourceHardness;
}

int ResourceTemplate::getID() {
    return resourceID;
}
