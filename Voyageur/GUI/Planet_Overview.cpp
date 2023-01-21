#include "Planet_Overview.h"

using namespace std;
using namespace ImGui;

Planet_Overview::Planet_Overview(MainGame &gameConstruct) : Game_Overview(gameConstruct) {
    showPlanetOverviewWindow = false;
    game = &gameConstruct;
}

/**
 * The main part of the class to show the planet window
 * @return If false when closed, stays true otherwise.
 */
bool Planet_Overview::PlanetWindowMain() {

    showPlanetOverviewWindow = true;
    if (showPlanetOverviewWindow) {
        ImGui::SetNextWindowSize(ImVec2(600, 500), ImGuiCond_FirstUseEver);
        Begin("Planet Overview",
              &showPlanetOverviewWindow,
              ImGuiWindowFlags_MenuBar);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

        MenuBar();
        //Left Pane;
        LeftPane();

        //Needed to have 2 panes next to one another
        ImGui::SameLine();

        // Right Pane
        RightPane();

        if (Button("Close Me")) {
            showPlanetOverviewWindow = false;
        }
        End();

    }
    return showPlanetOverviewWindow;
}

/**
 * The stored resources tab within the planet overview window
 * @return If it was successfully made. Not currently used
 */
bool Planet_Overview::StoredResourcesTab() {
    if (ImGui::BeginTabItem("Stored Resources")) {

        static ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable |
                                       ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV |
                                       ImGuiTableFlags_ContextMenuInBody;

        if (ImGui::BeginTable("StoredMineralTable", 3, flags)) {

            for (size_t row = 0;
                 row < game->planets.at(planetSelected)->GetStoredResources(ResourceSortOrder).size(); row++) {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++) {
                    ImGui::TableSetColumnIndex(column);
                    if (column == 0) {
                        ImGui::Text("%s",
                                    (game->planets.at(planetSelected)->GetStoredResources(ResourceSortOrder).at(
                                            row)->GetName()).c_str());
                    } else if (column == 1) {
                        ImGui::Text(
                                "%s", to_string(game->planets.at(planetSelected)->GetStoredResources(
                                        ResourceSortOrder).at(row)->GetAmount()).c_str());
                    } else if (column == 2) {
                        ImGui::Text(
                                "%s", to_string(game->planets.at(planetSelected)->GetStoredResources(
                                        ResourceSortOrder).at(row)->GetHardness()).c_str());
                    }
                }
            }
            ImGui::EndTable();
        }

        ImGui::EndTabItem();
        return true;
    }
    return false;
}


/**
 * The people tab within the planet overview window
 * @return If it was successfully made. Not currently used
 */
bool Planet_Overview::PeopleTab() {

    if (ImGui::BeginTabItem("People")) {

        vector<Person> peopleList = game->planets.at(planetSelected)->GetPeople();
        for (size_t row = 0; row < game->planets.at(planetSelected)->GetPeople().size(); row++) {

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
                ImGui::SetTooltip("Right-click for more info");
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
        return true;
    }

    return false;
}


/**
 * The mineral overview tab within the planet overview window
 * @return If it was successfully made. Not currently used
 */
bool Planet_Overview::MineralsTab() {
    if (ImGui::BeginTabItem("Minerals")) {
        //table
        static ImGuiTableFlags flags = ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_Resizable |
                                       ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV |
                                       ImGuiTableFlags_ContextMenuInBody;
        //PopStyleCompact();

        if (ImGui::BeginTable("MineralTable", 3, flags)) {

            for (size_t row = 0;
                 row < game->planets.at(planetSelected)->GetCurrentResources(ResourceSortOrder).size(); row++) {
                ImGui::TableNextRow();
                for (int column = 0; column < 3; column++) {
                    ImGui::TableSetColumnIndex(column);
                    if (column == 0) {
                        ImGui::Text("%s",
                                    (game->planets.at(planetSelected)->GetCurrentResources(ResourceSortOrder).at(
                                            row)->GetName()).c_str());
                    } else if (column == 1) {
                        ImGui::Text(
                                "%s", to_string(game->planets.at(planetSelected)->GetCurrentResources(
                                        ResourceSortOrder).at(row)->GetAmount()).c_str());
                    } else if (column == 2) {
                        ImGui::Text(
                                "%s", to_string(game->planets.at(planetSelected)->GetCurrentResources(
                                        ResourceSortOrder).at(row)->GetHardness()).c_str());
                    }
                }
            }
            ImGui::EndTable();
        }
        ImGui::EndTabItem();
        return true;
    }
    return false;
}

/**
 * The top menu of the planet overview window
 * @return Returns if it was successfully created.
 */
bool Planet_Overview::MenuBar() {
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
    return false;
}

/**
 * The left pane of the planet view window, shows the planets
 * @return if it was successfully built. TODO: Implement.
 */
bool Planet_Overview::LeftPane() {
    //The co-ords below represent the size of that part of the window. If they're 0, it just means go as big as needed.
    //The y co-ord here basically says to set it to the window size-10, allowing the close button to be visible without scrolling at the bottom.
    ImGui::BeginChild("Left Pane Planet Window", ImVec2(150, -ImGui::GetFrameHeightWithSpacing() - 10), true);
    for (size_t i = 0; i < game->planets.size(); i++) {
        // FIXME: Good candidate to use ImGuiSelectableFlags_SelectOnNav
        // FIXME: encounter issues if planets share name, or are removed.
        if (ImGui::Selectable((*game->planets.at(i)->name).c_str(), planetSelected == i))
            planetSelected = i;
    }
    ImGui::EndChild();
    return true;
}

/**
 * The right pane of the planet view window, shows info about the planets
 * @return if it was successfully built. TODO: Implement.
 */
bool Planet_Overview::RightPane() {
    ImGui::BeginGroup();
    //The following line was added in GUI Example
    ImGui::BeginChild("Right Pane Planet Window",
                      ImVec2(0, -ImGui::GetFrameHeightWithSpacing() - 10), true);

    //The name of the planet selected appears at the top.
    ImGui::Text((*game->planets.at(planetSelected)->name).c_str(), planetSelected);
    ImGui::Separator();
    //The start of the tabs in the window.
    if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None)) {
        if (ImGui::BeginTabItem("Description")) {
            ImGui::TextWrapped(
                    "First tab. Could contain a description of the planet, or maybe a very brief overview?");
            ImGui::EndTabItem();
        }
        MineralsTab();

        PeopleTab();

        StoredResourcesTab();

        ImGui::EndTabBar();
    }
    ImGui::EndChild();
    ImGui::EndGroup();
    return true;
}
