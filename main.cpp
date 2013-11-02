#include "Polycode.h"
#include "PolycodeView.h"
#include "utsuho.h"

int main(int argc, char *argv[]) {
	PolycodeView *view = new PolycodeView("Hello Polycode!");
	HelloPolycodeApp *app = new HelloPolycodeApp(view);
	while(app->Update()) {}
	return 0;
}
