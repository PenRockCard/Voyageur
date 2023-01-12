#include "MainGame.h";


MainGame::MainGame() {
    people = People();
    planets.push_back(new Planet("Neptune", &people));
    planets.push_back(new Planet("Mars", &people));
    updateTime = new UpdateTime();
}

void MainGame::Update() {

    updateTime->UpdateStart();

    for (Planet *planet: planets) {
        planet->mineResources();
    }

    updateTime->UpdateFinish();

}