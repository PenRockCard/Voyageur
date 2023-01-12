#include "Gui_Top_Menu.h"

using namespace std;
using namespace ImGui;

Gui_Top_Menu::Gui_Top_Menu(MainGame &gameConstruct) {
    game = gameConstruct;
    RecentUPS.resize(100);
}

void Gui_Top_Menu::Top_Menu_Bar() {

    //game = gameConstruct;

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New", "CTRL+N")) {}
            if (ImGui::MenuItem("Open", "CTRL+O")) {}
            if (ImGui::MenuItem("Save", "CTRL+S")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("FPS/UPS Menu")) {
            /*
            Ideas for FPS/UPS Window:
            Not resizable
            Has an x button
            Slider for UPS with input that updates based on slider (but will also accept new custom inputs?)
            Graph showing UPS history?
            ImGuiSliderFlags_AlwaysClamp
            Current FPS, from Hello World window
            */
            ImGui::MenuItem("Show Current FPS/UPS", NULL, &show_UPS_FPS);

            if (ImGui::BeginMenu("Modify UPS")) {
                //Modify these to call a method in here, as well as making sure they don't change the game object if it's being modified by the update method
                if (ImGui::MenuItem("1 UPS")) { UpdateUPS(1); }
                if (ImGui::MenuItem("10 UPS")) { UpdateUPS(10); }
                if (ImGui::MenuItem("50 UPS")) { UpdateUPS(50); }
                if (ImGui::MenuItem("60 UPS")) { UpdateUPS(60); }
                if (ImGui::MenuItem("100 UPS")) { UpdateUPS(100); }
                if (ImGui::MenuItem("250 UPS")) { UpdateUPS(250); }
                if (ImGui::MenuItem("500 UPS")) { UpdateUPS(500); }
                if (ImGui::MenuItem("750 UPS")) { UpdateUPS(750); }
                if (ImGui::MenuItem("1000 UPS")) { UpdateUPS(1000); }
                if (ImGui::MenuItem("No Limit")) { UpdateUPS(NULL); }
                if (ImGui::MenuItem("Custom")) { show_Custom_UPS_Window = true; }
                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();

    }
    if (show_UPS_FPS) {
        UPSWindow();
    }

    if (show_Custom_UPS_Window) {
        CustomUPSWindow();
    }
}

void Gui_Top_Menu::CustomUPSWindow() {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings;
    ImGui::Begin("Custom UPS", &show_Custom_UPS_Window, window_flags);
    ImGui::Text("Enter new UPS: ");
    static char buf2[64] = "";
    ImGui::InputText("##", buf2, 64, ImGuiInputTextFlags_CharsDecimal);

    //Checks if the enter key is pressed.
    if ((ImGui::IsKeyDown(ImGuiKey_Enter) || ImGui::IsKeyDown(ImGuiKey_KeypadEnter)) && buf2 != "") {
        UpdateUPS(atoi(buf2));
        show_Custom_UPS_Window = false;
    }
    if (ImGui::Button("Update")) {
        UpdateUPS(atoi(buf2));
        show_Custom_UPS_Window = false;
    }
    ImGui::End();
}

void Gui_Top_Menu::UpdateUPS(int UPSTime) {
    if (UPSTime == NULL) {
        game.updateTime->SetUpdateTime(NULL);
    } else {
        game.updateTime->SetUpdateTime(1e9 / UPSTime);
    }
}

void Gui_Top_Menu::UPSWindow() {

    ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove;

    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background

    //Sets the location
    const float PAD = 10.0f;
    const ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
    ImVec2 work_size = viewport->WorkSize;
    ImVec2 window_pos, window_pos_pivot;
    window_pos.x = work_pos.x + work_size.x - PAD;
    window_pos.y = work_pos.y + PAD;
    window_pos_pivot.x = 1.0f;
    window_pos_pivot.y = 0.0f;
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

    Begin("FPS/UPS Overview", &show_UPS_FPS, window_flags);

    //vector<long long>::iterator it;
    //it = RecentUPS.begin();
    //RecentUPS.erase(500);
    RecentUPS.at(vectorLocation) = game.updateTime->GetUpdateTime();

    if (vectorLocation != 99) {
        vectorLocation++;
    } else {
        vectorLocation = 0;
    }

    long long averageValue = 0;
    for (int i = 0; i < RecentUPS.size(); i++) {
        averageValue += RecentUPS.at(i);
    }
    float averageValueFloat = averageValue / ((float) RecentUPS.size());

    string UPSString = "UPS Ave: " + to_string(1e9 / averageValueFloat) + ". Updates happen in: " +
                       to_string(game.updateTime->GetActualUpdateTime()) + "ns";
    string UPSString2 = "UPS: " + to_string(1e9 / game.updateTime->GetUpdateTime()) + ". Updates happen in: " +
                        to_string(game.updateTime->GetActualUpdateTime()) + "ns";


    //Normally for UPS, it'd update time/second, but this only works this way (as this is the time for one update to happen).
    Text(UPSString.c_str());
    Text(UPSString2.c_str());

    Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / GetIO().Framerate, GetIO().Framerate);

    End();
}