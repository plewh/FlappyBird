#include "defs.h"
#include <ctime>
#include <cstdlib>

void InitRandom() {

	srandom(time(NULL));

}

int GetRandom(int a, int b) {

	return (random() + a) % b;

}
