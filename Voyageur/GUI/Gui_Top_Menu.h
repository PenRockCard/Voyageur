#pragma once
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

class Gui_Top_Menu {
    bool show_UPS_FPS = true;
    bool show_Custom_UPS_Window = false;
    vector<long long> RecentUPS;
    short vectorLocation = 0;
    MainGame *game;

    void UPSWindow();

    void UpdateUPS(int UPSTime);

    void CustomUPSWindow();

public:
    void Top_Menu_Bar();

    Gui_Top_Menu(MainGame &gameConstruct);
};

