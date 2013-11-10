/*
 * Player.h
 *
 *  Created on: Nov 2, 2013
 *      Author: jack
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <Polycode.h>
#include <PolycodeView.h>
#include "Polycode2DPhysics.h"

class Player : public Polycode::ScreenSprite, public Polycode::PhysicsScreenEntity{
public:
	Player();
	virtual ~Player();
};

#endif /* PLAYER_H_ */
