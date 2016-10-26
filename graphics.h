#ifndef __GRAPHICS__
#define __GRAPHICS__

#include "electric_field.h"

int main_window;
double aspect_ratio, window_width, window_height;
vector2d position;

void reshape_window (int width, int height);
void draw_window (void);
void update_charge_state (void);
void mouse_button (int button, int state, int x, int y);
vector2d screen_to_space (double x, double y);
void glut_key (unsigned char k, int x, int y);

#endif
