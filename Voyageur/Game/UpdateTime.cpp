/*
A class designed to measure, set and get the time it takes to update the game.
*/

#include "UpdateTime.h"

/*
The default constructor. Sets the minimum update time to 0.1 seconds.
TODO: Add another constructor to set it based on the time input?
*/
UpdateTime::UpdateTime() {
    //timePeriod = nanoseconds(100000000);
    timePeriod = nanoseconds(100000);
};

/*
Sets the start time for the beginning of the update.
*/
void UpdateTime::UpdateStart() {
    updateStartTime = high_resolution_clock::now();
}

/*
Finishes the update. Gets the current time, and compares it to the beginning time. This variable can be gotten via a getter below.
Then it'll sleep the thread long enough to meet the minimum update time.
TODO: Figure out what to do when the update time is shorter than the time it took to update the game?
*/
void UpdateTime::UpdateFinish() {


    updateFinishTime = high_resolution_clock::now();

    auto valueStart = updateStartTime.time_since_epoch();
    auto valueFinish = updateFinishTime.time_since_epoch();
    updateTotalTime = valueFinish - valueStart;

    this_thread::sleep_for(timePeriod - updateTotalTime);

    auto finalFinish = high_resolution_clock::now();
    updateOverallTime = finalFinish.time_since_epoch() - valueStart;

}

/*
Sets the minimum update time.
If null is entered, it means there is not min time, it'll go as fast as possible.
*/
bool UpdateTime::SetUpdateTime(long long newUpdateTime) {
    if (newUpdateTime == NULL) {
        timePeriod = nanoseconds(0);
    } else {
        timePeriod = nanoseconds(newUpdateTime);
    }
    return true;
}

/*
Returns the time (in nanoseconds) it actually took to update the game.
*/
long long UpdateTime::GetActualUpdateTime() {
    return updateTotalTime.count();
}

long long UpdateTime::GetUpdateTime() {
    return updateOverallTime.count();
}
