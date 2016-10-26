#ifndef __FIELD__
#define __FIELD__

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

#define SMALL_NUM 0.0000001
#define SCALE 1.0 // (m)
#define PREFERRED_WIDTH 1024
#define PREFERRED_HEIGHT 768
#define N_TRACK 1000

class vector2d {
  // Utility class for two-dimensional vector operations
public:
  vector2d() {x=0.0; y=0.0;}
  vector2d (double a, double b=0.0) {x=a; y=b;}
  vector2d operator+ (const vector2d &v) const { return vector2d(x+v.x, y+v.y); }
  vector2d operator- (const vector2d &v) const { return vector2d(x-v.x, y-v.y); }
  friend vector2d operator- (const vector2d &v) { return vector2d(-v.x, -v.y); }
  vector2d& operator+= (const vector2d &v) { x+=v.x; y+=v.y; return *this; }
  vector2d& operator-= (const vector2d &v) { x-=v.x; y-=v.y; return *this; }
  double operator* (const vector2d &v) const { return (x*v.x + y*v.y); }
  friend vector2d operator* (const vector2d &v, const double &a) { return vector2d(v.x*a, v.y*a); }
  friend vector2d operator* (const double &a, const vector2d &v) { return vector2d(v.x*a, v.y*a); }
  vector2d& operator*= (const double &a) { x*=a; y*=a; return *this; }
  vector2d operator/ (const double &a) const { return vector2d(x/a, y/a); }
  vector2d& operator/= (const double &a) { x/=a; y/=a; return *this; }
  double abs2() const { return (x*x + y*y); }
  double abs() const { return sqrt(this->abs2()); }
  vector2d norm() const { double s(this->abs()); if (s==0) return *this; else return vector2d(x/s, y/s); }
  friend ostream& operator << (ostream &out, const vector2d &v) { out << v.x << ' ' << v.y; return out; }
  double x, y;
private:
};

// Data type for recording test-charge's previous positions
struct track_t {
  unsigned short n;
  unsigned short p;
  vector2d pos[N_TRACK];
};

#ifdef DECLARE_GLOBAL_VARIABLES // actual declarations of all global variables for field_graphics.cpp

// GL windows and objects
int main_window;
double aspect_ratio, window_width, window_height;
vector2d position;

#else // extern declarations of those global variables used in lander.cpp

extern vector2d position;
extern double aspect_ratio, window_width, window_height;

#endif

// Mechanical simulation function prototypes
void update_dynamics (void);

// Graphics function prototypes
void reshape_window (int width, int height);
void draw_window (void);
void update_charge_state (void);
void mouse_button (int button, int state, int x, int y);
vector2d screen_to_space (double x, double y);
void glut_key (unsigned char k, int x, int y);

#endif
