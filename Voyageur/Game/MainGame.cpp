#include "MainGame.h";


MainGame::MainGame() {
    nextPlanetID = 0;
    nextResourceID = 0;
    GetResourceTemplates();
    people = People();
    planets.push_back(new Planet("Neptune", &people, nextPlanetID++, resourceTemplates));
    planets.push_back(new Planet("Mars", &people, nextPlanetID++, resourceTemplates));
    updateTime = new UpdateTime();
}

void MainGame::Update() {

    updateTime->UpdateStart();

    for (Planet *planet: planets) {
        planet->mineResources();
    }

    updateTime->UpdateFinish();

}

/**
 * Gets all the resource templates.
 * Currently it's all hardcoded, but ideally it'd pull them from an xml or json file.
 */
void MainGame::GetResourceTemplates() {
    resourceTemplates.push_back(new ResourceTemplate("Iron", 3.0, nextResourceID++));
    resourceTemplates.push_back(new ResourceTemplate("Tin", 2.0, nextResourceID++));
    resourceTemplates.push_back(new ResourceTemplate("Copper", 4.9, nextResourceID++));
    resourceTemplates.push_back(new ResourceTemplate("Coal", 0.5, nextResourceID++));
}
