#include "MainGame.h";


MainGame::MainGame() {
    planets.push_back(new Planet("Neptune"));
    planets.push_back(new Planet("Mars"));
    updateTime = new UpdateTime();
}

void MainGame::Update() {

    updateTime->UpdateStart();

    for (Planet *planet: planets) {
        planet->mineResources();
    }

    updateTime->UpdateFinish();

}