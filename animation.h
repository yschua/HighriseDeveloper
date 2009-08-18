#ifndef _ANIMATION_H
#define _ANIMATION_H
class animation : public body
{
private:
    std::vector<std::pair<sf::Image *, float> > m_frames;
    int m_current_frame;
    float m_time;
    
public:
    animation ();
    void add_frame (sf::Image * image, float duration);
    void update (float dt);
    sf::Sprite * sprite;
};
#endif
