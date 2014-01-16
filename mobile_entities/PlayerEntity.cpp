/*
 * 
 */

#include "PlayerEntity.h"

#include <PolyInputKeys.h>

using namespace Polycode;

void PlayerEntity::Update()
{
  //MobileEntity::Update();
  if(groundContacts < 0){
    // Floor the contacts count at 0
    groundContacts = 0;
  }
  if(groundContacts == 0){
    // Not grounded and not jumping
    if(!jumping){
      host->setVelocityY(this, fallSpeed);
    }
  }
  if(movingInputs == 0){
    host->setVelocityX(this, 0);
  }
}

void PlayerEntity::handleEvent(Event* rawEvent)
{
  PhysicsScreenEvent* event = (PhysicsScreenEvent*)rawEvent;
  switch(event->getEventCode()) {
    case PhysicsScreenEvent::EVENT_NEW_SHAPE_COLLISION:
      if(event->worldCollisionNormal.y > 0 && event->worldCollisionPoint.y > position.y){
	// Stop our vertical motion to prevent "slipping"
	host->setVelocityY(this, 0);
	box2dContacts.insert(event->contact);
	groundContacts++;
      }
      break;
    case PhysicsScreenEvent::EVENT_END_SHAPE_COLLISION:
      if(box2dContacts.find(event->contact) != box2dContacts.end()){
	box2dContacts.erase(event->contact);
	groundContacts--;
      }
      break;
  }
}


void PlayerEntity::onKeyDown(PolyKEY key, wchar_t charCode){
  if(ignoreKeys.find(key) != ignoreKeys.end()){
    return;
  }
   ignoreKeys.insert(key);
      switch(key){
	case KEY_SPACE:
	  host->setVelocityY(this, -fallSpeed*.667);
	  jumping = true;
	  break;
	case KEY_LEFT:
	  movingInputs++;
	  host->setVelocity(this, -runSpeed, host->getVelocity(this).y);
	  break;
	case KEY_RIGHT:
	  movingInputs++;
	  host->setVelocity(this, runSpeed, host->getVelocity(this).y);
	  break;
      }
}

void PlayerEntity::onKeyUp(PolyKEY key, wchar_t charCode) {
  if(ignoreKeys.find(key) == ignoreKeys.end()){
    return;
  }
  ignoreKeys.erase(key);
      switch(key){
	case KEY_SPACE:
	  jumping = false;
	  break;
	case KEY_LEFT:
	case KEY_RIGHT:
	  movingInputs--;
	  host->setVelocityX(this, 0);
	  break;
      }
}
