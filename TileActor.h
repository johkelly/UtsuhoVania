/*
 * TileActor.h
 *
 *  Created on: Nov 6, 2013
 *      Author: jack
 */

#ifndef TILEACTOR_H_
#define TILEACTOR_H_

#include <PolyScreenEntity.h>
#include <PolyScreenSprite.h>

#include "TileActorMediator.h"

class TileActor : public Polycode::ScreenSprite {
public:
	TileActorMediator* manager;

	TileActor(Polycode::String spriteSheet, int sWidth, int sHeight);

	void registerTo(TileActorMediator* manager) {this->manager = manager;}

	void move(Number dx, Number dy);

private:
};

#endif /* TILEACTOR_H_ */
