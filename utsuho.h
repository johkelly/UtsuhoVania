#include <Polycode.h>
#include <PolycodeView.h>
#include <Polycode2DPhysics.h>

using namespace Polycode;

class HelloPolycodeApp : public EventHandler {
public:
    HelloPolycodeApp(PolycodeView *view);
    ~HelloPolycodeApp();
    
    void handleEvent(Event* e);
    bool Update();

private:
	ScreenSprite* mSprite;
	PhysicsScreen* mScreen;
	Core *core;
	bool facingRight;
	bool moving;
	
	void setupAnimations();
};
