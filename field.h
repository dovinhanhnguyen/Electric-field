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

#define MARS_RADIUS 3386000.0 // (m)
#define PREFERRED_WIDTH 800
#define PREFERRED_HEIGHT 600
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

class vector3d {
  // Utility class for three-dimensional vector operations
public:
  vector3d() {x=0.0; y=0.0; z=0.0;}
  vector3d (double a, double b, double c=0.0) {x=a; y=b; z=c;}
  bool operator== (const vector3d &v) const { if ((x==v.x)&&(y==v.y)&&(z==v.z)) return true; else return false; }
  bool operator!= (const vector3d &v) const { if ((x!=v.x)||(y!=v.y)||(z!=v.z)) return true; else return false; }
  vector3d operator+ (const vector3d &v) const { return vector3d(x+v.x, y+v.y, z+v.z); }
  vector3d operator- (const vector3d &v) const { return vector3d(x-v.x, y-v.y, z-v.z); }
  friend vector3d operator- (const vector3d &v) { return vector3d(-v.x, -v.y, -v.z); }
  vector3d& operator+= (const vector3d &v) { x+=v.x; y+=v.y; z+=v.z; return *this; }
  vector3d& operator-= (const vector3d &v) { x-=v.x; y-=v.y; z-=v.z; return *this; }
  vector3d operator^ (const vector3d &v) const { return vector3d(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
  double operator* (const vector3d &v) const { return (x*v.x + y*v.y +z*v.z); }
  friend vector3d operator* (const vector3d &v, const double &a) { return vector3d(v.x*a, v.y*a, v.z*a); }
  friend vector3d operator* (const double &a, const vector3d &v) { return vector3d(v.x*a, v.y*a, v.z*a); }
  vector3d& operator*= (const double &a) { x*=a; y*=a; z*=a; return *this; }
  vector3d operator/ (const double &a) const { return vector3d(x/a, y/a, z/a); }
  vector3d& operator/= (const double &a) { x/=a; y/=a; z/=a; return *this; }
  double abs2() const { return (x*x + y*y + z*z); }
  double abs() const { return sqrt(this->abs2()); }
  vector3d norm() const { double s(this->abs()); if (s==0) return *this; else return vector3d(x/s, y/s, z/s); }
  friend ostream& operator << (ostream &out, const vector3d &v) { out << v.x << ' ' << v.y << ' ' << v.z; return out; }
  double x, y, z;
private:
};

// Data type for recording test-charge's previous positions
struct track_t {
  unsigned short n;
  unsigned short p;
  vector3d pos[N_TRACK];
};

#ifdef DECLARE_GLOBAL_VARIABLES // actual declarations of all global variables for field_graphics.cpp

// GL windows and objects
int main_window, closeup_window, orbital_window, instrument_window, view_width, view_height, win_width, win_height;
GLUquadricObj *quadObj;
vector3d position;

#else // extern declarations of those global variables used in lander.cpp

extern vector3d position;

#endif

// Mechanical simulation function prototypes
void update_dynamics (void);

// Graphics function prototypes
void reshape (int width, int height);
void draw (void);
void update_charge_state (void);
void mouse_button (int button, int state, int x, int y);
void glut_key (unsigned char k, int x, int y);

#endif
