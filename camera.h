#ifndef _CAMERA_H
#define _CAMERA_H
class camera : public body
{
private:
    int m_world_x, m_world_y, m_cam_x, m_cam_y;
    sf::RenderWindow * m_window;
    sf::Color m_back_color;
    static camera * m_instance;
    camera ();

public:
    static camera * get_instance ();
    void display ();
    void clear ();
    void draw (animation & to_draw);
    void set_max_framerate (int rate);
    void set_cam_size (int x, int y);
    void set_world_size (int x, int y);
    void create (const std::string & caption);
    void center (int x, int y);
    bool get_event (sf::Event & event);
};
#endif
