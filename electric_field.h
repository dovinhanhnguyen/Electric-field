#ifndef __ELECTRIC_FIELD__
#define __ELECTRIC_FIELD__

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
using namespace std;

#include "vector2d.h"

#define SMALL_NUM 0.0000001
#define SCALE 1.0 // (m)
#define PREFERRED_WIDTH 1024
#define PREFERRED_HEIGHT 768
#define N_TRACK 1000

// Data type for recording test-charge's previous positions
struct track_t {
  unsigned short n;
  unsigned short p;
  vector2d pos[N_TRACK];
};

extern vector2d position;
extern double aspect_ratio, window_width, window_height;

void update_dynamics (void);

#endif
