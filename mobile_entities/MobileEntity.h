/*
 * 
 */

#ifndef MOBILEENTITY_H
#define MOBILEENTITY_H

#include <PolyScenePrimitive.h>
#include <PolyPhysicsScreen.h>

class MobileEntity : public Polycode::ScenePrimitive
{
public:
  
MobileEntity(Polycode::PhysicsScene2D* physicsSource, int width, int height);
  
virtual void Update();
virtual void handleEvent(Polycode::Event* event);

virtual void forcePosition(Number x, Number y);

protected:
  
static const int fallSpeed = -15;

bool jumping = false;

Polycode::PhysicsScene2D* host;

};

#endif // MOBILEENTITY_H
