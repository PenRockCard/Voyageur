#include "Planet_Overview.h"

using namespace std;
using namespace ImGui;

Planet_Overview::Planet_Overview(MainGame &gameConstruct) : Game_Overview(gameConstruct) {
//    ResourceSortOrder = 0;
    show_planet_overview_window = false;
    game = &gameConstruct;
}

bool Planet_Overview::Planet_Window_Main() {

    show_planet_overview_window = true;
    if (show_planet_overview_window) {
        ImGui::SetNextWindowSize(ImVec2(600, 500), ImGuiCond_FirstUseEver);
        Begin("Planet Overview",
              &show_planet_overview_window,
              ImGuiWindowFlags_MenuBar);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Resource Sort Order")) {
                if (ImGui::MenuItem("None", NULL, (ResourceSortOrder == RESOURCE_ORDER_NONE))) {
                    ResourceSortOrder = RESOURCE_ORDER_NONE;
                }
                if (ImGui::MenuItem("Name", NULL, (ResourceSortOrder == RESOURCE_ORDER_NAME))) {
                    ResourceSortOrder = RESOURCE_ORDER_NAME;
                }
                if (ImGui::MenuItem("Amount", NULL, (ResourceSortOrder == RESOURCE_ORDER_AMOUNT))) {
                    ResourceSortOrder = RESOURCE_ORDER_AMOUNT;
                }
                if (ImGui::MenuItem("Hardness", NULL, (ResourceSortOrder == RESOURCE_ORDER_HARDNESS))) {
                    ResourceSortOrder = RESOURCE_ORDER_HARDNESS;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        // Left
        static int selected = 0;
        {
            ImGui::BeginChild("left pane", ImVec2(150, 0), true);
            for (int i = 0; i < game->planets.size(); i++) {
                // FIXME: Good candidate to use ImGuiSelectableFlags_SelectOnNav
                if (ImGui::Selectable((*game->planets.at(i)->name).c_str(), selected == i))
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
            ImGui::Text((*game->planets.at(selected)->name).c_str(), selected);
            ImGui::Separator();
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None)) {
                if (ImGui::BeginTabItem("Description")) {
                    ImGui::TextWrapped(
                            "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Minerals")) {
                    //table
                    static ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable |
                                                   ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV |
                                                   ImGuiTableFlags_ContextMenuInBody;
                    //PopStyleCompact();

                    if (ImGui::BeginTable("MineralTable", 3, flags)) {

                        for (size_t row = 0;
                             row < game->planets.at(selected)->GetCurrentResources(ResourceSortOrder).size(); row++) {
                            ImGui::TableNextRow();
                            for (int column = 0; column < 3; column++) {
                                ImGui::TableSetColumnIndex(column);
                                if (column == 0) {
                                    ImGui::Text("%s",
                                                (game->planets.at(selected)->GetCurrentResources(ResourceSortOrder).at(
                                                        row)->GetName()).c_str());
                                } else if (column == 1) {
                                    ImGui::Text(
                                            "%s", to_string(game->planets.at(selected)->GetCurrentResources(
                                                    ResourceSortOrder).at(row)->GetAmount()).c_str());
                                } else if (column == 2) {
                                    ImGui::Text(
                                            "%s", to_string(game->planets.at(selected)->GetCurrentResources(
                                                    ResourceSortOrder).at(row)->GetHardness()).c_str());
                                }
                            }
                        }
                        ImGui::EndTable();
                    }
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("People")) {

                    vector<Person> peopleList = game->planets.at(selected)->GetPeople();
                    for (size_t row = 0; row < game->planets.at(selected)->GetPeople().size(); row++) {

                        /**
                         * This part is more a temporary solution to show off how right clicking something to bring up a pop up would work
                         * The double hashes in the selectable are needed, the popup (and most ImGui parts I think) use the labels as their unique ids
                         * This can lead to collisions, causing them to be called multiple times in some scenarios
                         * Here that scenario are 2+ people sharing the same name, which is solved by silently attaching their id at the end
                         * More info here:
                         * https://github.com/ocornut/imgui/blob/9d6b2b096b20fa654c84fd8bb4d9631c250b33d6/imgui.cpp#L637
                         */
                        ImGui::Selectable(
                                (peopleList.at(row).GetName() + "##" + to_string(peopleList.at(row).GetID())).c_str());
                        if (ImGui::IsItemHovered()) {
                            ImGui::SetTooltip("Right-click to open popup");
                        }
                        if (ImGui::BeginPopupContextItem()) { // <-- use last item id as popup id
                            ImGui::Text(to_string(peopleList.at(row).GetPlanet()).c_str());
                            ImGui::Text((peopleList.at(row).GetName()).c_str());
                            ImGui::Text(to_string(peopleList.at(row).GetID()).c_str());
                            if (ImGui::Button("Close"))
                                ImGui::CloseCurrentPopup();
                            if (ImGui::Button("Delete Person")) {
                                game->people.DeletePerson(peopleList.at(row).GetID());
                                ImGui::CloseCurrentPopup();
                            }
                            ImGui::EndPopup();
                        }
                    }

                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("Stored Resources")) {

                    static ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable |
                                                   ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV |
                                                   ImGuiTableFlags_ContextMenuInBody;

                    if (ImGui::BeginTable("StoredMineralTable", 3, flags)) {

                        for (size_t row = 0;
                             row < game->planets.at(selected)->GetStoredResources(ResourceSortOrder).size(); row++) {
                            ImGui::TableNextRow();
                            for (int column = 0; column < 3; column++) {
                                ImGui::TableSetColumnIndex(column);
                                if (column == 0) {
                                    ImGui::Text("%s",
                                                (game->planets.at(selected)->GetStoredResources(ResourceSortOrder).at(
                                                        row)->GetName()).c_str());
                                } else if (column == 1) {
                                    ImGui::Text(
                                            "%s", to_string(game->planets.at(selected)->GetStoredResources(
                                                    ResourceSortOrder).at(row)->GetAmount()).c_str());
                                } else if (column == 2) {
                                    ImGui::Text(
                                            "%s", to_string(game->planets.at(selected)->GetStoredResources(
                                                    ResourceSortOrder).at(row)->GetHardness()).c_str());
                                }
                            }
                        }
                        ImGui::EndTable();
                    }

                    ImGui::EndTabItem();
                }

                ImGui::EndTabBar();
            }
            ImGui::EndChild();
            ImGui::EndGroup();
        }


        if (Button("Close Me")) {
            show_planet_overview_window = false;
//            End();
//            return false;
        }
        End();


        return show_planet_overview_window;
    }

}
