// FirstGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


//#include "imgui_demo_start.h"
#include "GUI/Gui_Start.h"
#include <iostream>
#include "Game/MainGame.h"

using namespace std;

bool showDemo = false;
void GUI_Start();
void Main_Update();
MainGame* game = new MainGame();
int endGame = -1;

int main() {
    //Main loop, temp. Move to MainGame.cpp maybe?
    thread threadUpdate(Main_Update);
    thread threadGUI(GUI_Start);

    threadUpdate.join();
    threadGUI.join();

    return 0;
}

void GUI_Start() {
    endGame = main_window_start(*game);
}

void Main_Update() {
    while (endGame==-1) {
        game->Update();
    }
}