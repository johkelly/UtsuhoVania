/*
 * TilePlatformerApp.cpp
 *
 *  Created on: Nov 8, 2013
 *      Author: jack
 */

#include <PolyScreenSprite.h>
#include "TilePlatformerApp.h"

using namespace Polycode;

TilePlatformerApp::TilePlatformerApp(PolycodeView *view) {
	core = new POLYCODE_CORE(view, 640, 480, false, false, 0, 0, 90);

	//core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);

	screen = new TileScreen(1, 10);

	actor = new TileActor("Resources/megatiles.png", 17, 17);
	actor->setShapeSize(17, 34);
	actor->setHitbox(17, 34);
	actor->addAnimation("idleRight", "23", 1);
	actor->playAnimation("idleRight", 0, false);
	screen->addTileActor(actor);

	const int ts = Tile::TILE_SIZE;
	for(int i = 60; i > 0; --i){
		Tile* t = new Tile("Resources/megatiles.png", "0");
		int x = rand() % 30;
		int y = rand() % 30;
		screen->addTile(t, x, y);
		tiles.push_back(t);
	}
	actor->setPosition(ts*17, ts*17);
}

void TilePlatformerApp::handleEvent(Event* e){
	CoreInput* coreInput = core->getInput();

	if(e->getDispatcher() == coreInput) {
		InputEvent *inputEvent = (InputEvent*)e;

		switch(e->getEventCode()) {
		case InputEvent::EVENT_KEYDOWN:
			switch (inputEvent->keyCode()) {
			case KEY_LEFT:
				actor->move(-3, 0);
				break;
			case KEY_RIGHT:
				actor->move(3, 0);
				break;
			case KEY_UP:
				actor->move(0, -3);
				break;
			case KEY_DOWN:
				actor->move(0, 3);
				break;
			}
			break;
		}
	}
}

bool TilePlatformerApp::Update(){
	CoreInput* ci = core->getInput();
	double dx = 0;
	double dy = 0;
	dx += (ci->getKeyState(KEY_LEFT) ? -2 : 0);
	dx += (ci->getKeyState(KEY_RIGHT) ? 2 : 0);
	dy += (ci->getKeyState(KEY_UP) ? -7 : 0);
	dy += (ci->getKeyState(KEY_DOWN) ? 2 : 0);
	dy += 5;
	if(dx != 0 || dy != 0){
		actor->move(dx, dy);
	}
	return core->updateAndRender();
}
