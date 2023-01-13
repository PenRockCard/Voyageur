#include "MainGame.h";


MainGame::MainGame() {
    nextPlanetID=0;
    people = People();
    planets.push_back(new Planet("Neptune", &people,nextPlanetID++));
    planets.push_back(new Planet("Mars", &people,nextPlanetID++));
    updateTime = new UpdateTime();
}

void MainGame::Update() {

    updateTime->UpdateStart();

    for (Planet *planet: planets) {
        planet->mineResources();
    }

    updateTime->UpdateFinish();

}