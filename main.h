#ifndef MAIN_H
#define MAIN_H

#include "constants.h"
#include "vector.h"
#include "matrixd.h"
#include "complex.h"
#include "mandle.h"

#include "lib/write_screen/drawlib.h"

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include <curses.h>

typedef struct mandle_controls {
	char is_running;
	int depth;
	long double zoom;
	long double R;
	long double I;
} MANDLE_CONTROLS;

//entrypoint, init and start opengl
extern int main();


#endif
