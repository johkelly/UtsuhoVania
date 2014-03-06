/*
 * 
 */

#include "PlatformerScreen.h"

using namespace Polycode;

PlatformerScreen::PlatformerScreen(Number worldScale, Number freq, int velIters, int posIters) 
: PhysicsScene2D(worldScale, freq, velIters, posIters)
{
  setGravity(Vector2(0, 0));
}
