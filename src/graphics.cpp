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
  
  // Draw charges
  glPushMatrix();
  glBegin(GL_POINTS);
  
  // source
  for (int i=0; i<MAX_NUM_SOURCE; i++) {
    if (list_of_source_charges[i].draw_or_not == 1) {
      if (list_of_source_charges[i].minus_or_plus == 0) glColor3f(0.0, 1.0, 1.0);
      else glColor3f(1.0, 0.0, 0.0);
      glVertex3d(list_of_source_charges[i].charge_position.x, list_of_source_charges[i].charge_position.y, 0.0);
    }
  }
  
  // test
  glColor3f(1.0, 1.0, 0.0);
  for (int i=0; i<MAX_NUM_TEST; i++){
    if (list_of_test_charges[i].draw_or_not == 1) {
      glVertex3d(list_of_test_charges[i].charge_position.x, list_of_test_charges[i].charge_position.y, 0.0);
    }
  }
  glEnd();
  glPopMatrix();
  
  glutSwapBuffers();
}

void update_charge_state (void)
  // The GLUT idle function, called every time round the event loop
{
  // Update charge states
  for (int i=0; i<MAX_NUM_TEST; i++) {
    if (list_of_test_charges[i].draw_or_not == 1) {
      list_of_test_charges[i].update_charge();
      list_of_test_charges[i].detect_collision(aspect_ratio);
    }
  }

  // Refresh the visualization
  draw_window();
}

void mouse_button (int button, int state, int x, int y)
  // Callback for mouse button presses in the orbital view window
{
  if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
    list_of_test_charges[test_charge_index].draw_or_not = 1;
    list_of_test_charges[test_charge_index].charge_position = screen_to_space((double)x,(double)y);
    test_charge_index += 1;
    if (test_charge_index>=MAX_NUM_TEST) test_charge_index -= MAX_NUM_TEST;
  }
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
    for(int i=0; i<MAX_NUM_TEST; i++) {
      list_of_test_charges[i].reset_charge(vector2d(0.0, 0.0));
    }
    break;
  
  case '2':
    // Dipole
    initialise_charges(k-'0');
    for(int i=0; i<MAX_NUM_TEST; i++) {
      list_of_test_charges[i].reset_charge(vector2d(0.0, 0.0));
    }
    break;
  
  case '3':
    // Quadrupole
    initialise_charges(k-'0');
    for(int i=0; i<MAX_NUM_TEST; i++) {
      list_of_test_charges[i].reset_charge(vector2d(0.0, 0.0));
    }
    break;
  }
}

void initialise_charges (int scenario)
  // Initialise charges at the beginning of a simulation
{
  glPointSize(5.0);
  
  // Initialise source charges
  switch (scenario) {
  
  case 1:
    list_of_source_charges[0].draw_or_not = 1;
    list_of_source_charges[0].minus_or_plus = 0;
    list_of_source_charges[0].charge_position = vector2d(0.0, 0.0);
    
    list_of_source_charges[1].draw_or_not = 0;
    list_of_source_charges[1].minus_or_plus = 0;
    list_of_source_charges[1].charge_position = vector2d(0.0, 0.0);
    
    list_of_source_charges[2].draw_or_not = 0;
    list_of_source_charges[2].minus_or_plus = 0;
    list_of_source_charges[2].charge_position = vector2d(0.0, 0.0);
    
    list_of_source_charges[3].draw_or_not = 0;
    list_of_source_charges[3].minus_or_plus = 0;
    list_of_source_charges[3].charge_position = vector2d(0.0, 0.0);
    break;
  
  case 2:
    list_of_source_charges[0].draw_or_not = 1;
    list_of_source_charges[0].minus_or_plus = 0;
    list_of_source_charges[0].charge_position = vector2d(0.0, SCALE/4);
    
    list_of_source_charges[1].draw_or_not = 1;
    list_of_source_charges[1].minus_or_plus = 0;
    list_of_source_charges[1].charge_position = vector2d(0.0, -SCALE/4);
    
    list_of_source_charges[2].draw_or_not = 0;
    list_of_source_charges[2].minus_or_plus = 0;
    list_of_source_charges[2].charge_position = vector2d(0.0, 0.0);
    
    list_of_source_charges[3].draw_or_not = 0;
    list_of_source_charges[3].minus_or_plus = 0;
    list_of_source_charges[3].charge_position = vector2d(0.0, 0.0);
    break;
  
  case 3:
    list_of_source_charges[0].draw_or_not = 1;
    list_of_source_charges[0].minus_or_plus = 0;
    list_of_source_charges[0].charge_position = vector2d(SCALE/4, SCALE/4);
    
    list_of_source_charges[1].draw_or_not = 1;
    list_of_source_charges[1].minus_or_plus = 0;
    list_of_source_charges[1].charge_position = vector2d(-SCALE/4, SCALE/4);
    
    list_of_source_charges[2].draw_or_not = 1;
    list_of_source_charges[2].minus_or_plus = 0;
    list_of_source_charges[2].charge_position = vector2d(-SCALE/4, -SCALE/4);
    
    list_of_source_charges[3].draw_or_not = 1;
    list_of_source_charges[3].minus_or_plus = 0;
    list_of_source_charges[3].charge_position = vector2d(SCALE/4, -SCALE/4);
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
  glutDisplayFunc(draw_window);
  glutReshapeFunc(reshape);
  glutIdleFunc(update_charge_state);
  glutMouseFunc(mouse_button);
  glutKeyboardFunc(glut_key);
  
  // Initialise test charges
  for(int i=0; i<MAX_NUM_TEST; i++) {
    list_of_test_charges[i].test_or_source = 1;
    list_of_test_charges[i].ptr_source_list = list_of_source_charges;
  }
  test_charge_index = 0;
  
  // Initialise source charges and enter GLUT loop
  initialise_charges(3);
  glutMainLoop();
  
  return 0;
}
