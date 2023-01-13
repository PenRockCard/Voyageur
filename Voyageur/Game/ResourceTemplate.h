//
// Created by Chris on 2023-01-13.
//

#ifndef VOYAGEUR_RESOURCETEMPLATE_H
#define VOYAGEUR_RESOURCETEMPLATE_H

#include <string>

using namespace std;


class ResourceTemplate {

    string resourceName;
    float resourceHardness;
    int resourceID;

public:
    ResourceTemplate(string name, float hardness, int ID);

    string getName();
    float getHardness();
    int getID();

    /**
     * Consider adding this? Don't see a use currently
     */
    //ResourceTemplate getDetails();
};


#endif //VOYAGEUR_RESOURCETEMPLATE_H
