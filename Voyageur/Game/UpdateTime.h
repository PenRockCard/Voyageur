#pragma once

#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

class UpdateTime {
    //The current minimum update time.
    chrono::nanoseconds timePeriod;

    //The start time of the current update.
    steady_clock::time_point updateStartTime;

    //The finish time of the update.
    steady_clock::time_point updateFinishTime;

    //How long it took to update the game
    nanoseconds updateTotalTime;

    //How long it took to update the game including the delay
    nanoseconds updateOverallTime;

public:
    UpdateTime();

    void UpdateStart();

    void UpdateFinish();

    bool SetUpdateTime(long long newUpdateTime);

    long long GetUpdateTime();

    long long GetActualUpdateTime();

};

