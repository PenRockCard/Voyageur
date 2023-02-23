#include "MainGame.h";


MainGame::MainGame() {
    nextPlanetID = 0;
    nextResourceID = 0;
    GetResourceTemplates();
    people = People();
    //TODO: Add sun distance and angle offset to parameters
    planets.push_back(new Planet("Mercury", &people, nextPlanetID++, resourceTemplates, 0.466697*AU, 0.307499*AU, 360));
    planets.push_back(new Planet("Venus", &people, nextPlanetID++, resourceTemplates, 0.728213 * AU, 0.718440 * AU, 360));
    planets.push_back(new Planet("Earth", &people, nextPlanetID++, resourceTemplates, 152097597, 147098450, 360));
    planets.push_back(new Planet("Mars", &people, nextPlanetID++, resourceTemplates, 1.66621*AU, 1.3814*AU, 360));
    planets.push_back(new Planet("Jupiter", &people, nextPlanetID++, resourceTemplates, 5.4570*AU, 4.9506*AU, 360));
    planets.push_back(new Planet("Saturn", &people, nextPlanetID++, resourceTemplates, 10.1238*AU,9.0412*AU, 360));
    planets.push_back(new Planet("Uranus", &people, nextPlanetID++, resourceTemplates, 20.0965*AU,18.2861*AU, 360));
    planets.push_back(new Planet("Neptune", &people, nextPlanetID++, resourceTemplates, 30.33*AU,29.81*AU,  360));
    planets.push_back(new Planet("Pluto", &people, nextPlanetID++, resourceTemplates, 49.305*AU,29.658*AU,  360));

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
