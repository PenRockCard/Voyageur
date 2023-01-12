#pragma once

#include <vector>
#include "Planet.h"
#include <chrono>
#include <thread>
#include "UpdateTime.h"

using namespace std;

class MainGame {

public:
    vector<Planet *> planets;

    MainGame();

    void Update();

    UpdateTime *updateTime = new UpdateTime();

};

