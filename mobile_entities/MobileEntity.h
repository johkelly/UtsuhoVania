/*
 * 
 */

#ifndef MOBILEENTITY_H
#define MOBILEENTITY_H

#include <PolyScreenShape.h>
#include <PolyPhysicsScreen.h>
#include <PolyInputKeys.h>
#include <PolyGlobals.h>

#include <set>

class MobileEntity : public Polycode::ScreenShape
{
public:
  
MobileEntity(Polycode::PhysicsScreen* physicsSource, int width, int height);
  
virtual void Update();
virtual void handleEvent(Polycode::Event* event);

virtual void forcePosition(Number x, Number y);

protected:
  
static const int fallSpeed = 15;

bool jumping = false;
  
int groundContacts;
std::set<b2Contact*> box2dContacts;
Polycode::PhysicsScreen* host;

};

#endif // MOBILEENTITY_H
