#pragma once

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx11.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <tchar.h>
#include "../Game/MainGame.h"

class Planet_Overview {
    MainGame game;
    bool show_planet_overview_window = false;
public:
    Planet_Overview(MainGame &gameConstruct);

    void Planet_Window_Main();
};

