#include "Planet_Overview.h"
#include "../Game/MainGame.h"

using namespace std;
using namespace ImGui;

Planet_Overview::Planet_Overview(MainGame &gameConstruct) {
    show_planet_overview_window = false;
    game = gameConstruct;
}

void Planet_Overview::Planet_Window_Main() {

    show_planet_overview_window = true;
    if (show_planet_overview_window) {
        ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
        Begin("Planet Overview",
              &show_planet_overview_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

        // Left
        static int selected = 0;
        {
            ImGui::BeginChild("left pane", ImVec2(150, 0), true);
            for (int i = 0; i < game.planets.size(); i++) {
                // FIXME: Good candidate to use ImGuiSelectableFlags_SelectOnNav
                if (ImGui::Selectable((*game.planets.at(i)->name).c_str(), selected == i))
                    selected = i;
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();

        // Right
        {
            ImGui::BeginGroup();
            ImGui::BeginChild("item view",
                              ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
            ImGui::Text((*game.planets.at(selected)->name).c_str(), selected);
            ImGui::Separator();
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None)) {
                if (ImGui::BeginTabItem("Description")) {
                    ImGui::TextWrapped(
                            "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Resources")) {
                    //table
                    static ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable |
                                                   ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV |
                                                   ImGuiTableFlags_ContextMenuInBody;
                    //PopStyleCompact();

                    if (ImGui::BeginTable("table1", 3, flags)) {

                        for (size_t row = 0; row < game.planets.at(selected)->resources.size(); row++) {
                            ImGui::TableNextRow();
                            for (int column = 0; column < 3; column++) {
                                ImGui::TableSetColumnIndex(column);
                                if (column == 0) {
                                    ImGui::Text((*game.planets.at(selected)->resources.at(row)->name).c_str());
                                } else if (column == 1) {
                                    ImGui::Text(
                                            to_string(*game.planets.at(selected)->resources.at(row)->amount).c_str());
                                } else if (column == 2) {
                                    ImGui::Text(
                                            to_string(*game.planets.at(selected)->resources.at(row)->hardness).c_str());
                                }
                            }
                        }
                        ImGui::EndTable();
                    }

                    ImGui::Text("ID: 0123456789");
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::EndChild();
            if (ImGui::Button("Revert")) {}
            ImGui::SameLine();
            if (ImGui::Button("Save")) {}
            ImGui::EndGroup();
        }


        if (Button("Close Me")) {
            show_planet_overview_window = false;
        }
        End();
    }

}
