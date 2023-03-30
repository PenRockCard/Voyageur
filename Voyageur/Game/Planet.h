#pragma once

#include <iostream>
#include <vector>
#include "Resource.h"
#include "Person.h"
#include "People.h"
#include "ResourceTemplate.h"
#include <unordered_map>
#include "../Constants.h"
#include "../Resources/EllipseFunction.h"
#include <random>

class Planet {

    People *people;
    unsigned long long ID;
    vector<Resource *> mineableResources;
    vector<Resource *> storedResources;
    unordered_map<int, int> resourceLocationTable;


    static bool compareResourceAmount(Resource r1, Resource r2);

    static bool compareResourceName(Resource r1, Resource r2);

    static bool compareResourceHardness(Resource r1, Resource r2);


public:

    EllipseFunction *planetOrbit;

    int *temperature = new int;

    void mineResources();

    unsigned long long GetID();

    string *name = new string;

    Planet(string nameConstructor, People *peopleConstructor, unsigned long long planetIDConstructor,
           vector<ResourceTemplate *> resourceTemplates, double OrbitLong, double OrbitShort, int orbitPoints, double orbitOffSetX = 0, double orbitOffSetY = 0, double orbitAngle = 0);

    vector<Person> GetPeople();

    vector<Resource *> GetCurrentResources(int order);

    vector<Resource *> GetStoredResources(int order);
};


