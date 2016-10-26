#ifndef __VECTOR2D__
#define __VECTOR2D__

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

#endif
