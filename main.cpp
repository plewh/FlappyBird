#include "app.h"

int main() {

	App* app = new App;
	app->Run();

	delete(app);
	return 0;

}
