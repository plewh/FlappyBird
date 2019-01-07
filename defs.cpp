#include "defs.h"
#include <cstdio>

void PrintLog(int line, const char* func, const char* file, char* comment) {

	fprintf(stderr, "[-](%s)|%s %s:%d| %s\n", __TIME__, file, func, line, comment);

}
