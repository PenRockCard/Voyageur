//
// Created by Chris on 2023-02-21.
//

#ifndef VOYAGEUR_SYSTEMWINDOW_H
#define VOYAGEUR_SYSTEMWINDOW_H

#include "Game_Overview.h"
#include "../implot/implot.h"

class SystemWindow : public Game_Overview  {
    MainGame *game;
    bool showSystemWindowWindow = false;

public:
    //Don't think the explict keyword is needed here
    SystemWindow(MainGame &gameConstruct);

    bool ShowWindow();
};


#endif //VOYAGEUR_SYSTEMWINDOW_H
