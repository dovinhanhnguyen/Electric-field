// Implementation for graphics
// dvan2, Oct 2016

#include "graphics.h"

void reshape (int width, int height)
  // Reshape and set up matrices
{
  window_width = glutGet(GLUT_WINDOW_WIDTH);
  window_height = glutGet(GLUT_WINDOW_HEIGHT);
  aspect_ratio = window_width/window_height;
  
  glutSetWindow(main_window);
  glViewport(0, 0, window_width, window_height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-SCALE*aspect_ratio, SCALE*aspect_ratio, -SCALE, SCALE, -1.0, 1.0);
}

void draw_window (void)
  // Draw main GLUT window
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  // TO DO: put this in a class
  glPushMatrix();
  glColor3f(0.0, 1.0, 1.0);
  glPointSize(3.0);
  glBegin(GL_POINTS);
  glVertex3d(position.x, position.y, 0.0);
  glEnd();
  glPopMatrix();
  
  glutSwapBuffers();
}

void update_charge_state (void)
  // The GLUT idle function, called every time round the event loop
{
  // TO DO: Update charge states

  // Refresh the visualization
  draw_window();
}

void mouse_button (int button, int state, int x, int y)
  // Callback for mouse button presses in the orbital view window
{
  if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) position = screen_to_space((double)x, (double)y);
}

vector2d screen_to_space (double x, double y)
  // Convert position of mouse click in window to 2D coordinates in space
{
  return vector2d((x*2.0*SCALE*aspect_ratio/window_width-SCALE*aspect_ratio), (SCALE-y*2.0*SCALE/window_height));
}

void glut_key (unsigned char k, int x, int y)
  // Callback for key presses in all windows
{
  switch(k) {
    
  case 27: case 'q': case 'Q':
    // Escape or q or Q  - exit
    exit(0);
    break;
  
  case '1':
    // Monopole
    initialise_charges(k-'0');
    break;
  
  case '2':
    // Dipole
    initialise_charges(k-'0');
    break;
  
  case '3':
    // Quadrupole
    initialise_charges(k-'0');
    break;
  }
}

void initialise_charges (int scenario)
  // TO DO: Initialise charges at the beginning of a simulation
{
}

int main (int argc, char* argv[])
  // Initializes GLUT windows and charge state, then enters GLUT main loop
{
  // Main GLUT window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(PREFERRED_WIDTH, PREFERRED_HEIGHT);
  main_window = glutCreateWindow("Electric field (Anh Nguyen, October 2016)");
  glDrawBuffer(GL_BACK);
  glutDisplayFunc(draw_window);
  glutReshapeFunc(reshape);
  glutIdleFunc(update_charge_state);
  glutMouseFunc(mouse_button);
  glutKeyboardFunc(glut_key);
  
  initialise_charges(0);
  glutMainLoop();
  
  return 0;
}
