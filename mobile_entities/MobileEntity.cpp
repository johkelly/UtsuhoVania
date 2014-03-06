/*
 * 
 */

#include <PolyPhysicsScreenEntity.h>

#include <iostream>

#include "MobileEntity.h"

using namespace Polycode;

MobileEntity::MobileEntity(PhysicsScene2D* physicsSource, int width, int height) : ScenePrimitive(ScenePrimitive::TYPE_PLANE, width, height)
{
  host = physicsSource;
  setWidth(width);
  setHeight(height);
  host->addPhysicsChild(this, PhysicsScreenEntity::ENTITY_RECT, false, 0, 0, 0, false, true);
  host->addEventListener(this, PhysicsScene2DEvent::EVENT_NEW_SHAPE_COLLISION);
  host->addEventListener(this, PhysicsScene2DEvent::EVENT_END_SHAPE_COLLISION);
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
