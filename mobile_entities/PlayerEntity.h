/*
 * 
 */

#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H

#include <mobile_entities/MobileEntity.h>

#include <set>

class PlayerEntity : public MobileEntity
{
public:
  
PlayerEntity(Polycode::PhysicsScene2D* physicsSource, int width, int height) : MobileEntity(physicsSource, width, height), groundContacts(0) {}
  
  virtual void Update();
  virtual void handleEvent(Polycode::Event* event);
  virtual void onKeyDown(Polycode::PolyKEY key);
  virtual void onKeyUp(Polycode::PolyKEY key);

private:
  static const int runSpeed = 7;
  
  int movingInputs = 0;
  
  int groundContacts;
  std::set<b2Contact*> box2dContacts;

  std::set<Polycode::PolyKEY> ignoreKeys;

};

#endif // PLAYERENTITY_H
