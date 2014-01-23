/*
 * 
 */

#ifndef PLATFORMERSCREEN_H
#define PLATFORMERSCREEN_H

#include <PolyPhysicsScreen.h>

#include "MobileEntity.h"

class PlatformerScreen : public Polycode::PhysicsScreen
{
public:
PlatformerScreen(Number worldScale, Number freq, int velIters = 10, int posIters = 10);
//virtual void Update();

//std::vector<MobileEntity> entities;

};

#endif // PLATFORMERSCREEN_H
