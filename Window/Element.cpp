// Element

#include <iostream>
#include "../Types/Vector2.h"
#include "../Camera.h"

#include "Element.h"

namespace UI
{
   ElementStyle::ElementStyle()
   {
      ActiveColor = sf::Color(255,255,255,255);
      InActiveColor = sf::Color(255,255,255,150);
      DisabledColor = sf::Color(0,0,0,100);
   }
   Element::Element()
   {
      Enabled = true;
      Active = false;
   }
   void Element::SetParent(Window* NewParent)
   {
      ParentWindow = NewParent;
   }
   void Element::DeActivate()
   {
      Active = false;
   }

   void Element::Activate()
   {
      Active = true;
   }

   void Element::SetAction(std::string Key, ActionType Action) {
      Actions[Key] = Action;
   }
}
