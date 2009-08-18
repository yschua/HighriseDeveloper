#ifndef _IMAGE_H
#define _IMAGE_H
class image_manager
{
private:
    std::string m_path_prefix;
    std::map<std::string, sf::Image *> m_images;
    static image_manager * m_instance;
    image_manager ();
    
public:
    static image_manager * get_instance ();
    sf::Image * get_image (const std::string & name);
    int preload_image (const std::string & name);
    void set_path (const std::string & prefix);
};
#endif
