/*
 * 
 */

#ifndef MOBILEENTITY_H
#define MOBILEENTITY_H

#include <PolyScreenShape.h>
#include <PolyPhysicsScreen.h>
#include <PolyInputKeys.h>
#include <PolyGlobals.h>

class MobileEntity : public Polycode::ScreenShape
{
public:
  
MobileEntity(Polycode::PhysicsScreen* physicsSource, int height);
  
virtual void Update();
virtual void handleEvent(Polycode::Event* event);

virtual void forcePosition(Number x, Number y);

protected:
  
static const int jumpSpeed = 10;
static const int runSpeed = 7;

bool jumping = false;
  
int groundContacts;
Polycode::PhysicsScreen* host;

};

#endif // MOBILEENTITY_H
