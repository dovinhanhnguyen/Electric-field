#define DECLARE_GLOBAL_VARIABLES
#include "field.h"

void reshape (int width, int height)
  // Reshape and set up matrices
{
  width = glutGet(GLUT_WINDOW_WIDTH);
  height = glutGet(GLUT_WINDOW_HEIGHT);
  
  double aspect_ratio;
  aspect_ratio = (double)width/(double)height;
  
  glutSetWindow(main_window);
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2.0*MARS_RADIUS*aspect_ratio, 2.0*MARS_RADIUS*aspect_ratio, -2.0*MARS_RADIUS, 2.0*MARS_RADIUS, -100.0*MARS_RADIUS, 100.0*MARS_RADIUS);
}

void draw (void)
  // Draw main GLUT window
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  // put this in a class
  glPushMatrix();
  glColor3f(0.0, 1.0, 1.0);
  glPointSize(3.0);
  glBegin(GL_POINTS);
  glVertex3d(position.x, position.y, position.z);
  glEnd();
  glPopMatrix();
  
  glutSwapBuffers();
}

void update_charge_state (void)
  // The GLUT idle function, called every time round the event loop
{
  // Mechanical dynamics
  update_dynamics();

  // Refresh the visualization
  draw();
}

void mouse_button (int button, int state, int x, int y)
  // Callback for mouse button presses in the orbital view window
{
}

void glut_key (unsigned char k, int x, int y)
  // Callback for key presses in all windows
{
  switch(k) {
    
  case 27: case 'q': case 'Q':
    // Escape or q or Q  - exit
    exit(0);
    break;
  }
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
  glutDisplayFunc(draw);
  glutReshapeFunc(reshape);
  glutIdleFunc(update_charge_state);
  glutMouseFunc(mouse_button);
  glutKeyboardFunc(glut_key);
  quadObj = gluNewQuadric();
  
  glutMainLoop();
  
  return 0;
}
