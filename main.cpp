#include "app.h"
#include "defs.h"

int main() {

	Log("Flappy Bird Clone - Dec 2018 - By plewh");

	App* app = new App;

	Log("Init complete, App running");

	app->Run();

	Log("App stopped, cleaning up...");

	delete(app);

	Log("Cleanup complete, bye!");

	return 0;

}
