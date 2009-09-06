#pragma once

#include <SFML/Graphics.hpp>

#include "Element.h"
//#include "../Graphics/Graphics.h"
#include "Window.h"

namespace UI
{
   class Button : public Element
   {
   private:
      sf::Shape mButtonBG;
      sf::String* mpButtonText;
      sf::Rect<int> mRect;

   public:
      Button();
      virtual ~Button();

      void Draw();
      void Update();
      void SetPosition(int, int);
      void SetActualPosition(int, int);
      void SetText( const char* pszText )
      {
         mpButtonText = new sf::String(pszText);
      }
      sf::Vector2i GetPosition();
      bool OnEvent(const sf::Event&);
      void SetSize(int, int);
      sf::Vector2i GetSize();
      const sf::Rect<int>& GetRect();
      bool Contains(Vector2i Mouse);
      void MouseIn();
      void MouseOut();
   protected:
      void SetParent(Window* NewParent);
      void DeActivate();
      void Activate();
   };
}
