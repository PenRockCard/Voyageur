#pragma once

#include <vector>
#include "Planet.h"
#include <chrono>
#include <thread>
#include "UpdateTime.h"
#include "People.h"

using namespace std;

class MainGame {

    unsigned long long nextPlanetID;

public:
    vector<Planet *> planets;

    People people;

    MainGame();

    void Update();

    UpdateTime *updateTime = new UpdateTime();

};

