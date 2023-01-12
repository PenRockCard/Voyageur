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

int main()
{
    if (showDemo) {
        cout << "Ahahaha, there's no demo\n";
        return 0;
    }

    //initial window

    //main_window_start(*game);

    //main_window_start();
    //Main loop, temp. Move to MainGame.cpp maybe?
    thread threadUpdate(Main_Update);
    thread threadGUI(GUI_Start);


    threadUpdate.join();
    threadGUI.join();


    int x = 5;

    return 0;
}

void GUI_Start() {
    main_window_start(*game);
}

void Main_Update() {
    while (true) {
        game->Update();
    }
}