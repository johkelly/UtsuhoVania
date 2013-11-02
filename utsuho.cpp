#include "utsuho.h"

HelloPolycodeApp::HelloPolycodeApp(PolycodeView *view) : EventHandler() {
	facingRight = true;
	moving = false;
	
	core = new POLYCODE_CORE(view, 640,480,false,false,0,0,90);

	CoreServices::getInstance()->getResourceManager()->addArchive("Resources/default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYDOWN);
	core->getInput()->addEventListener(this, InputEvent::EVENT_KEYUP);

	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST);
	Screen *screen = new Screen();
	ScreenSprite *sprite = new ScreenSprite("Resources/MegaManSheetEven.png", 32, 32);
	mSprite = sprite;
	sprite->setPosition(350,150);
	sprite->setScale(1,1);
	screen->addChild(sprite);
	setupAnimations();
	mSprite->playAnimation("idleRight", 0, false);
}

void HelloPolycodeApp::setupAnimations(){
	mSprite->addAnimation("walkRight", "1,2,3,2", .16);
	mSprite->addAnimation("walkLeft", "5,6,7,6", .16);
	mSprite->addAnimation("jumpRight", "11", 1);
	mSprite->addAnimation("jumpLeft", "15", 1);
	mSprite->addAnimation("idleRight", "23", 1);
	mSprite->addAnimation("idleLeft", "26", 1);
}

void HelloPolycodeApp::handleEvent(Event* e){
	CoreInput* coreInput = core->getInput();
	if(e->getDispatcher() == coreInput) {
		InputEvent *inputEvent = (InputEvent*)e;
		
		switch(e->getEventCode()) {
			case InputEvent::EVENT_KEYDOWN:
				switch (inputEvent->keyCode()) {
					case KEY_SPACE:
						mSprite->playAnimation((facingRight? "jumpRight" : "jumpLeft"), 0, false);
						break;
					case KEY_LEFT:
						facingRight = false;
						moving = true;
						if(coreInput->getKeyState(KEY_SPACE)){
							mSprite->playAnimation("jumpLeft", 0, false);
						} else {
							mSprite->playAnimation("walkLeft", 0, false);
						}
						break;
					case KEY_RIGHT:
						facingRight = true;
						moving = true;
						if(coreInput->getKeyState(KEY_SPACE)){
							mSprite->playAnimation("jumpRight", 0, false);
						} else {
							mSprite->playAnimation("walkRight", 0, false);
						}
						break;
				}
			break;
			case InputEvent::EVENT_KEYUP:
				switch (inputEvent->key) {
					case KEY_SPACE:
						if(coreInput->getKeyState(KEY_RIGHT)){
							mSprite->playAnimation("walkRight", 0, false);
						} else if(coreInput->getKeyState(KEY_LEFT)){
							mSprite->playAnimation("walkLeft", 0, false);
						} else {
							mSprite->playAnimation((facingRight? "idleRight" : "idleLeft"), 0, false);
						}
						break;
					case KEY_LEFT:
					case KEY_RIGHT:
						moving = false;
						if(coreInput->getKeyState(KEY_SPACE)){
							mSprite->playAnimation((facingRight? "jumpRight" : "jumpLeft"), 0, false);
						} else {
							mSprite->playAnimation((facingRight? "idleRight" : "idleLeft"), 0, false);
						}
						break;
				}
			break;			
		}
		
	}
}

HelloPolycodeApp::~HelloPolycodeApp() {
}

bool HelloPolycodeApp::Update() {
	if(moving){
		mSprite->Translate((facingRight? 1 : -1), 0, 0);
	}
    return core->updateAndRender();
}
