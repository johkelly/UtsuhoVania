/*
 * TilePlatformerApp.h
 *
 *  Created on: Nov 8, 2013
 *      Author: jack
 */

#ifndef TILEPLATFORMERAPP_H_
#define TILEPLATFORMERAPP_H_

#include <Polycode.h>
#include <PolycodeView.h>
#include <PolyEventHandler.h>
#include "TileScreen.h"

class TilePlatformerApp: public Polycode::EventHandler {
public:
	TilePlatformerApp(Polycode::PolycodeView *view);

    void handleEvent(Polycode::Event* e);
    bool Update();

private:
    Polycode::Core* core;
    TileScreen* screen;
    std::vector<Tile*> tiles;
    TileActor* actor;
};

#endif /* TILEPLATFORMERAPP_H_ */
