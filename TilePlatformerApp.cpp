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

	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);

	screen = new TileScreen(1, 10);

	actor = new TileActor("Resources/megatiles.png", 17, 17);
	actor->setShapeSize(17, 34);
	actor->setScale(1, 1);
	actor->setHitbox(17, 34);
	actor->addAnimation("idleRight", "23", 1);
	actor->playAnimation("idleRight", 0, false);
	screen->addTileActor(actor);

	const int ts = Tile::TILE_SIZE;
	for(int i = 20; i > 0; --i){
		Tile* t = new Tile("Resources/megatiles.png", "0");
		t->setHitbox(17, 17);
		int x = rand() % 15;
		int y = rand() % 15;
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
					actor->move(-7, 0);
					break;
				case KEY_RIGHT:
					actor->move(7, 0);
					break;
				case KEY_UP:
					actor->move(0, -7);
					break;
				case KEY_DOWN:
					actor->move(0, 7);
					break;
				}
				break;
		}
	}
}

bool TilePlatformerApp::Update(){
	return core->updateAndRender();
}
