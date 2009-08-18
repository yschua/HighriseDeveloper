#ifndef _PHYSICS_H
#define _PHYSICS_H

typedef std::pair<float, float> vector2;

class body
{
protected:
    vector2 m_s, m_v, m_a;
    
public:
    body (float x, float y);
    body ();
    float get_position_x ();
    float get_position_y ();
    float get_velocity_x ();
    float get_velocity_y ();
    float get_acceleration_x ();
    float get_acceleration_y ();
    vector2 get_position ();
    vector2 get_velocity ();
    vector2 get_acceleration ();
    void debug_print ();
    void set_position (float x, float y);
    void set_velocity (float x, float y);
    void set_acceleration (float x, float y);
    void integrate (float dt);
};
#endif
