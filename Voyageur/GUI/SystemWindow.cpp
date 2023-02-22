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
        ImGui::Text("Pluto and Neptune Graph");

        //The -1,-1 makes it fit to the frame (basically as big as possible)
        if (ImPlot::BeginPlot("##PlotTesting",ImVec2(-1,-1),ImPlotFlags_Equal|ImPlotFlags_NoFrame|ImPlotFlags_NoMouseText)) {
            for (size_t row = 0; row <game->planets.size(); row++) {
                ImPlot::PlotLine(game->planets.at(row)->name->c_str(),
                                 game->planets.at(row)->planetOrbit->GetXArray(),
                                 game->planets.at(row)->planetOrbit->GetYArray(),
                                 game->planets.at(row)->planetOrbit->GetNumberPoints());
            }
//            ImPlot::PlotLine("Pluto", xArrayPluto, yArrayPluto, plutoOrbit->GetNumberPoints());
//            ImPlot::PlotLine("Neptune", xArrayNeptune, yArrayNeptune, neptuneOrbit->GetNumberPoints());
            ImPlot::EndPlot();
        }

        ImGui::End();
    }

    return showSystemWindowWindow;
}