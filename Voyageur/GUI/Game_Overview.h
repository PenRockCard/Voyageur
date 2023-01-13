#pragma once

#include <iostream>
#include <compare>
#include <vector>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx11.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <tchar.h>
#include "../Game/MainGame.h"

static int ResourceSortOrder;

class Game_Overview {
    MainGame game;
protected:
    bool show_planet_window = false;
public:
    Game_Overview(MainGame &gameConstruct);

    void CreateOverviewWindow();


};

