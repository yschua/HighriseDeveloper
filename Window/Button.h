#pragma once

#include <SFML/Graphics.hpp>

#include "Element.h"
//#include "../Graphics/Graphics.h"
#include "Window.h"

namespace hr {
    namespace UI {
        class Button : public Element {
            public:
            Button();
            void Draw();
            void Update();
            void SetPosition(int, int);
            void SetActualPosition(int, int);
            sf::Vector2i GetPosition();
            bool OnEvent(const sf::Event&);
            void SetSize(int, int);
            sf::Vector2i GetSize();
            const sf::Rect<int>& GetRect();
            bool Contains(int, int);
            void MouseIn();
            void MouseOut();
            protected:
            void SetParent(Window* NewParent);
            void DeActivate();
            void Activate();
            private:
            sf::Shape ButtonBG;
            sf::String ButtonText;
            sf::Rect<int> Rect;
        };
    }
}
