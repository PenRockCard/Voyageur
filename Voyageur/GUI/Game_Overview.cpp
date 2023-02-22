#include "Game_Overview.h"
//TODO: See if it's possible to move these 2 includes to the .h file
#include "SystemWindow.h"
#include "PlanetOverview.h"

using namespace std;
using namespace ImGui;

Game_Overview::Game_Overview(MainGame &gameConstruct) {

    show_planet_window = false;
    showSolarSystem = false;
    game = &gameConstruct;

    ResourceSortOrder = 0;
    planetSelected = 0;

}

void Game_Overview::CreateOverviewWindow() {


    Begin("Game Overview");

    //Number of planets
    string tempString2 = "The number of planets is: " + to_string(game->planets.size());
    Text(tempString2.c_str());

    for (int i = 0; i < game->planets.size(); i++) {
        string tempPlanetString = "Planet: " + *game->planets.at(i)->name;
        Text(tempPlanetString.c_str());
    }

    //Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
    Checkbox("Planet Info Window", &show_planet_window);
    Checkbox("Solar System Overview", &showSolarSystem);
    End();

    //If the checkbox is checked, the show planet window will be shown.
    if (show_planet_window) {
        PlanetOverview planetOverview = PlanetOverview(*game);
        show_planet_window=planetOverview.PlanetWindowMain();
    }

    if (showSolarSystem) {
        SystemWindow systemWindow = SystemWindow(*game);
        showSolarSystem = systemWindow.ShowWindow();
    }
}
