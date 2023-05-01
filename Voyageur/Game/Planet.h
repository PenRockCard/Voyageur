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
#include <math.h>

//Debatable types
//Used for an array/vector containing the planets orbital characteristics throughout it's orbit to make calculating it's current position, etc, easier
struct PlanetOrbitalCharacteristics{
    double angle;
    double velocity;
    double time;
    double distance;
    double distanceFromOrbitCenter;
};

class Planet {

    People *people;
    unsigned long long ID;
    vector<Resource *> mineableResources;
    vector<Resource *> storedResources;
    unordered_map<int, int> resourceLocationTable;
    vector<PlanetOrbitalCharacteristics> orbitalCharacteristics;
    double currentAngle; //Limit of 0-360, either in deg or rad.

    long long totalSeconds; //The total orbit time
    int *timePerTick;

    static bool compareResourceAmount(Resource r1, Resource r2);

    static bool compareResourceName(Resource r1, Resource r2);

    static bool compareResourceHardness(Resource r1, Resource r2);


public:

    double GetCurrentAngle();
    int GetOrbitalCharacteristicsSize();

    int orbitalCharacteristicsPosition; //Current location the planet is in the orbitalCharacteristics vector. If it's between two points there, it should be in the lower one.

    PlanetOrbitalCharacteristics GetOrbitCharacteristicAt(int position);

    EllipseFunction *planetOrbit;

    int *temperature = new int;

    void mineResources();

    void UpdateLocation();

    unsigned long long GetID();

    string *name = new string;

    Planet(string nameConstructor, People *peopleConstructor, unsigned long long planetIDConstructor,
           vector<ResourceTemplate *> resourceTemplates, double OrbitLong, double OrbitShort, int orbitPoints, int orbitalCharacteristicPoints, double planetMass, int *timePerTickConstructor, double orbitOffSetX = 0, double orbitOffSetY = 0, double orbitAngle = 0);

    vector<Person> GetPeople();

    vector<Resource *> GetCurrentResources(int order);

    vector<Resource *> GetStoredResources(int order);
};


