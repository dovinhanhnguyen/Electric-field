// Header file for Charge class
// dvan2, Oct 2016

#ifndef __CHARGE__
#define __CHARGE__

#include "vector2d.h"

#define SMALL_NUM 0.0000001
#define PERMITTIVITY 8.85E-12 // (F/m)
#define CHARGE 1.60E-19 // (C)
#define MASS 9.11E-31 // (kg)
#define MAX_NUM_SOURCE 4
#define MAX_NUM_TEST 10
#define DELTA_T 0.2 // (s)
#define SCALE 100.0 // (m)

class Charge {
  public:
    // Data members
    int test_or_source; // 1 for test charge, 0 for source charge
    int draw_or_not; // 1 if charge is to be drawn, 0 if it is not
    int minus_or_plus; // 1 for negative charge, 0 for positive charge; test charge is always positive
    vector2d charge_position;
    vector2d previous_charge_position;
    vector2d charge_velocity;
    vector2d charge_acceleration;
    Charge* ptr_source_list;
    
    // Constructors
    Charge() {test_or_source = 0; draw_or_not = 0; minus_or_plus = 0; charge_position = vector2d(0.0, 0.0); previous_charge_position = vector2d(0.0, 0.0); charge_velocity = vector2d(0.0, 0.0); charge_acceleration = vector2d(0.0, 0.0); ptr_source_list = NULL;}
    Charge(int test_charge, int draw_charge, int sign_of_charge, vector2d initial_position, Charge list_of_source[]);
    
    // Member functions
    vector2d field_generated (vector2d r);
    void acceleration (void);
    void update_charge (void);
    void reset_charge (vector2d initial_position);
    void detect_collision (double aspect_ratio);
  private:
};

#endif
