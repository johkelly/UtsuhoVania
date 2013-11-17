/*
 * TileActorMediator.h
 *
 *  Created on: Nov 8, 2013
 *      Author: jack
 */

#ifndef TILEACTORMEDIATOR_H_
#define TILEACTORMEDIATOR_H_

#include <PolyScreenEntity.h>

class TileActorMediator {
public:
	TileActorMediator() {}
	virtual ~TileActorMediator() {}
	virtual void runMovement(Polycode::ScreenEntity* s, Number dx, Number dy) = 0;
};

#endif /* TILEACTORMEDIATOR_H_ */
