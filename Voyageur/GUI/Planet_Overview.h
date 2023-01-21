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

/**
 * A class for the GUI of the planet overview window. Inherits from the Game Overview class so that it can keep it's constants while open.
 */
class Planet_Overview : public Game_Overview {
    MainGame *game;
    bool showPlanetOverviewWindow = false;

public:
    Planet_Overview(MainGame &gameConstruct);

    bool StoredResourcesTab();

    bool PeopleTab();

    bool MineralsTab();

    bool PlanetWindowMain();

    bool MenuBar();

    bool LeftPane();

    bool RightPane();
};

