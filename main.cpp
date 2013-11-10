#include "Polycode.h"
#include "PolycodeView.h"
#include "utsuho.h"
#include "TilePlatformerApp.h"

int main(int argc, char *argv[]) {
	PolycodeView *view = new PolycodeView("Hello Polycode!");
	//HelloPolycodeApp *app = new HelloPolycodeApp(view);
	TilePlatformerApp* app = new TilePlatformerApp(view);
	while(app->Update()) {}
	return 0;
}
