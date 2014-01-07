/*
 * 
 */

#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H

#include <mobile_entities/MobileEntity.h>

class PlayerEntity : public MobileEntity
{
public:
  
PlayerEntity(Polycode::PhysicsScreen* physicsSource, int width, int height) : MobileEntity(physicsSource, width, height) {}
  
  virtual void Update();
virtual void onKeyDown(Polycode::PolyKEY key, wchar_t charCode);
virtual void onKeyUp(Polycode::PolyKEY key, wchar_t charCode);

private:
  static const int runSpeed = 7;
  
  int movingInputs = 0;

};

#endif // PLAYERENTITY_H
