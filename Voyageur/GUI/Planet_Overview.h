#pragma once

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx11.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <tchar.h>
#include "../Game/MainGame.h"
#include "../Constants.h"
#include "Game_Overview.h"

class Planet_Overview: public Game_Overview {
    MainGame *game;
    bool show_planet_overview_window = false;

public:
    Planet_Overview(MainGame &gameConstruct);

    bool Planet_Window_Main();
};

