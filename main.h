#ifndef MAIN_H
#define MAIN_H

#include "constants.h"
#include "vector.h"
#include "matrixd.h"
#include "complex.h"
#include "mandel.h"

#include "lib/write_screen/drawlib.h"

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <assert.h>

#include <curses.h>

// for writing to a file
#include <sys/stat.h>
#include <fcntl.h>

#define LOG_MUTEXES
#define MUTEX_FNAME "mutex_logfile"

typedef struct mandle_controls {
	char is_running;
	int depth;
	long double zoom;
	long double R;
	long double I;
} MANDLE_CONTROLS;

#define MIN_JOB_SIZE 256
#define T_WORKING (char)0
#define T_LOOKING (char)1
#define T_IDLE (char)2
struct tdraw_data {
	pthread_t tid;
	int idx;
	int num_threads;
	MANDLE_CONTROLS *cont;
	pthread_mutex_t state_mutex;
	char state;
	pthread_mutex_t bounds_mutex;
	// tells each thread to interrupt mid-draw
	char frame_update;
	int TLx;
	int TLy;
	int BRx;
	int BRy;
};

void display(MANDLE_CONTROLS *cont);

//threads:
// 1: mark as idle
// 2: wait to be told to work
// (loop):
//	3: take a job slot
//		or break to go back to 1 if no jobs
//	4: set as working
//	== do the work ==
//	5: set as finished

#ifdef LOG_MUTEXES
int logfile_fd;
pthread_mutex_t logfile_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

/* signals to the controller that the thread is waiting */
pthread_mutex_t currently_idle_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  currently_idle_cond  = PTHREAD_COND_INITIALIZER;
int currently_idle;

/* signals to the thread they can take a job */
pthread_mutex_t stay_idle_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t stay_idle_cond = PTHREAD_COND_INITIALIZER;
char stay_idle;

// tells the drawer controller to interrupt all threads and restart
pthread_mutex_t frame_update_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t frame_update_cond = PTHREAD_COND_INITIALIZER;
char frame_update;

pthread_mutex_t currently_working_mutex= PTHREAD_MUTEX_INITIALIZER;
int currently_working;

/**
 * makes a RGBT value out of a number (0-255)
 */
void make_colour(double val, RGBT *ret);

void make_smooth_colour(int val, RGBT *ret, com *z);

#ifndef PI
#define PI 3.14159f
#endif

#ifndef MIN
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#endif
#ifndef MAX
#define MAX(X,Y) ((X) < (Y) ? (Y) : (X))
#endif
#ifndef ABS
#define ABS(X) ((X) < 0 ? -1 * (X) : (X))
#endif

//entrypoint, init and start opengl
extern int main();


#endif
