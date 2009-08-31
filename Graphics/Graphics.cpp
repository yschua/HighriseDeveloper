#include "Graphics.h"
#include <SFML/Graphics.hpp>

#include "../Settings/Settings.h"

namespace hr {
    namespace Gfx {
        std::map<std::string, sf::Image> Images;
        sf::Image* GetImage(std::string Key) {
            if (Images.find(Key) == Images.end()) {
                std::cout << "Loading image " << Key << '\n';
                sf::Image Image;
                if (!Image.LoadFromFile("gfx/" + Settings::Get("Apperance.GraphicsPack")
                    + "/" + Key)) {
                        if (!Image.LoadFromFile(Key)) {
                            if (!Image.LoadFromFile("room/" + Key)) {
                                if (!Image.LoadFromFile("gfx/original/" + Key)) {
                                    std::cout << "WARNING: Failed to load image " << Key << "\n";
                                    //Image.Create(32, 32, sf::Color(255,0,0,255));
                                    Image.LoadFromPixels(64, 64, ErrorImagePixels);
                                }
                            }
                        }
                    }
                Images[Key] = Image;
            }
            Images[Key].SetSmooth(false);
            return &Images[Key];
        }
    }
}



