/*
 * TileActor.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: jack
 */

#include "TileActor.h"

TileActor::TileActor(Polycode::String spriteSheet, int sWidth, int sHeight) : Polycode::ScreenSprite(spriteSheet, sWidth, sHeight), manager(0x0) {
	setPosition(0,0);
	setScale(1,1);
}

void TileActor::move(int dx, int dy){
	if(manager != 0x0){
		manager->runMovement(this, dx, dy);
	}
	Translate(dx, dy, 0);
}
