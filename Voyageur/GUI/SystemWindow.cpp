//
// Created by Chris on 2023-02-21.
//

#include "SystemWindow.h"

SystemWindow::SystemWindow(MainGame &gameConstruct) : Game_Overview(gameConstruct) {

    showSystemWindowWindow = false;
    game = &gameConstruct;

}

bool SystemWindow::ShowWindow() {

    showSystemWindowWindow = true;
    if (showSystemWindowWindow) {
        ImGui::Begin("System Overview", &showSystemWindowWindow);
        ImGui::Text("Sol Overview");

        //The -1,-1 makes it fit to the frame (basically as big as possible)
        if (ImPlot::BeginPlot("##PlotTesting", ImVec2(-1, -1),
                              ImPlotFlags_Equal | ImPlotFlags_NoFrame | ImPlotFlags_NoMouseText)) {
            for (size_t row = 0; row < game->planets.size(); row++) {
                ImPlot::PlotLine(game->planets.at(row)->name->c_str(),
                                 game->planets.at(row)->planetOrbit->GetXArray(),
                                 game->planets.at(row)->planetOrbit->GetYArray(),
                                 game->planets.at(row)->planetOrbit->GetNumberPoints());

                //Part to plot the planets current location.
                int orbitalCharacteristicsPosition = game->planets.at(row)->orbitalCharacteristicsPosition;
                int nextOrbitalCharacteristicsPosition = (((orbitalCharacteristicsPosition + 1) >=
                                                           game->planets.at(row)->GetOrbitalCharacteristicsSize())
                                                          ? 0 : (orbitalCharacteristicsPosition + 1));
                PlanetOrbitalCharacteristics p1 = game->planets.at(row)->GetOrbitCharacteristicAt(
                        orbitalCharacteristicsPosition);
                PlanetOrbitalCharacteristics p2 = game->planets.at(row)->GetOrbitCharacteristicAt(
                        nextOrbitalCharacteristicsPosition);
                //Finds the mid distance from orbit center
                double distance = p1.distanceFromOrbitCenter +
                                  (p2.distanceFromOrbitCenter - p1.distanceFromOrbitCenter) *
                                  (game->planets.at(row)->GetCurrentAngle() - p1.angle) / (p2.angle - p1.angle);
                double xDistance[1]{distance * cos(game->planets.at(row)->GetCurrentAngle())};
                double yDistance[1]{distance * sin(game->planets.at(row)->GetCurrentAngle())};

                ImPlot::PlotScatter(game->planets.at(row)->name->c_str(), xDistance, yDistance, 1);
                if ((game->planets.at(row)->GetID)() == 6) {
                    //cout << game->planets.at(row)->GetCurrentAngle() << " GUI\n" << endl;
                }

            }
            ImPlot::EndPlot();
        }

        ImGui::End();
    }

    return showSystemWindowWindow;
}