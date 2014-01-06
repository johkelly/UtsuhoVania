/*
 * 
 */

#include <PolyScreenShape.h>
#include <PolyPhysicsScreenEntity.h>

#include <iostream>

#include "MobileEntity.h"

using namespace Polycode;

MobileEntity::MobileEntity(PhysicsScreen* physicsSource, int height) : ScreenShape(ScreenShape::SHAPE_RECT, 1, height), groundContacts(0)
{
  host = physicsSource;
  host->addPhysicsChild(this, PhysicsScreenEntity::ENTITY_RECT, false, 0, 1, 0, false, true);
  host->addEventListener(this, PhysicsScreenEvent::EVENT_NEW_SHAPE_COLLISION);
  host->addEventListener(this, PhysicsScreenEvent::EVENT_END_SHAPE_COLLISION);
  colorAffectsChildren = false;
  color.a = 0;
}

void MobileEntity::Update()
{
  if(groundContacts < 0){
    // Floor the contacts count at 0
    groundContacts = 0;
  }
  if(groundContacts == 0){
    // Not grounded and falling
    if(!jumping){
      host->setVelocityY(this, jumpSpeed*1.5);
    }
  }
}

void MobileEntity::handleEvent(Event* rawEvent)
{
  PhysicsScreenEvent* event = (PhysicsScreenEvent*)rawEvent;
  switch(event->getEventCode()) {
    case PhysicsScreenEvent::EVENT_NEW_SHAPE_COLLISION:
      // Stop our vertical motion to prevent "slipping"
      host->setVelocityY(this, 0);
      groundContacts++;
      break;
    case PhysicsScreenEvent::EVENT_END_SHAPE_COLLISION:
      groundContacts--;
      break;
  }
}

void MobileEntity::forcePosition(Number x, Number y) {
  host->stopTrackingChild(this);
  setPosition(x, y);
  host->addPhysicsChild(this, PhysicsScreenEntity::ENTITY_RECT, false, 0, 1, 0, false, true);
}
