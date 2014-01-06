/*
 * 
 */

#include "PlayerEntity.h"

#include <PolyInputKeys.h>

using namespace Polycode;

void PlayerEntity::Update()
{
  MobileEntity::Update();
  if(movingInputs == 0){
    host->setVelocityX(this, 0);
  }
}


void PlayerEntity::onKeyDown(PolyKEY key, wchar_t charCode){
      switch(key){
	case KEY_SPACE:
	  host->setVelocityY(this, -jumpSpeed);
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
