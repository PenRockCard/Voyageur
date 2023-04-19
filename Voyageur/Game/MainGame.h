#pragma once

#include <vector>
#include "Planet.h"
#include <chrono>
#include <thread>
#include "UpdateTime.h"
#include "People.h"
#include "ResourceTemplate.h"

using namespace std;

class MainGame {

    unsigned long long nextPlanetID;
    int nextResourceID;
    vector<ResourceTemplate *> resourceTemplates;
    void GetResourceTemplates();

public:
    vector<Planet *> planets;

    People people;

    int timePerTick; //Number of seconds passed every update/tick.

    MainGame();

    void Update();

    UpdateTime *updateTime = new UpdateTime();

};

