/*
 * 
 */

#include <PolyScreenShape.h>
#include <PolyPhysicsScreenEntity.h>

#include <iostream>

#include "MobileEntity.h"

using namespace Polycode;

MobileEntity::MobileEntity(PhysicsScreen* physicsSource, int width, int height) : ScreenShape(ScreenShape::SHAPE_RECT, width, height)
{
  host = physicsSource;
  host->addPhysicsChild(this, PhysicsScreenEntity::ENTITY_RECT, false, 0, 0, 0, false, true);
  host->addEventListener(this, PhysicsScreenEvent::EVENT_NEW_SHAPE_COLLISION);
  host->addEventListener(this, PhysicsScreenEvent::EVENT_END_SHAPE_COLLISION);
  colorAffectsChildren = false;
  color.a = 0;
}

void MobileEntity::Update()
{
}

void MobileEntity::handleEvent(Event* rawEvent)
{
  host->setVelocityX(this, 0);
  host->setVelocityY(this, 0);
}

void MobileEntity::forcePosition(Number x, Number y) {
  host->stopTrackingChild(this);
  setPosition(x, y);
  host->addPhysicsChild(this, PhysicsScreenEntity::ENTITY_RECT, false, 0, 1, 0, false, true);
}
