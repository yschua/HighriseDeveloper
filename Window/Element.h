#pragma once

#include <SFML/Graphics.hpp>
//#include <loki/Functor.h>  // AC pulled LOKI for now
//#include "../Graphics/Graphics.h"
#include "../highrisedev.h"

//#include "Window.h"

namespace UI
{
   /// This class is used exclusivly for changing the style of UI
   /// elements in the different states.
   class Window;
   class ElementStyle
   {
   public:
      ElementStyle();
      sf::Color ActiveColor;
      sf::Color InActiveColor;
      sf::Color DisabledColor;
   };
   //////////////////////////////////////////////////////////////////
   /// You cannnot create instances of this class directly, you must
   /// create instances of a derived class instead. All UI elements
   /// must inheriet from this base class.
   //////////////////////////////////////////////////////////////////

   template <typename T> class FunkyT  // the Functor
   {
      T* mT;
   public:
      FunkyT()
      {
         mT = NULL;
         // TODO: nothing happening here crazy, car to implement
      }
      FunkyT(T* pT)
         : mT(pT)
      {
         // TODO: nothing happening here crazy, car to implement
      }
   };

   class Element
   {
   public:
      Element();
      virtual void Draw()=0;
      virtual void Update()=0;
      virtual bool OnEvent(const sf::Event& Event)=0;
      virtual void SetSize(int XSize, int YSize)=0;
      virtual sf::Vector2<int> GetSize()=0;
      virtual void SetPosition(int XPos, int YPos)=0;
      virtual sf::Vector2<int> GetPosition()=0;
      virtual const sf::Rect<int>& GetRect()=0;
      virtual bool Contains(Vector2i Mouse)=0;
      virtual void MouseIn()=0;
      virtual void MouseOut()=0;
      //            typedef Loki::Functor<void, LOKI_TYPELIST_1(Element*)> ActionType;
      typedef FunkyT<Element*> ActionType;
      void SetAction(std::string Key, ActionType Action);
      //friend class OT::Window;
      //friend class EventMgr;
      //protected:
      void SetParent(Window* NewParent);
      virtual void DeActivate();
      virtual void Activate();
   protected:
      bool Enabled;
      bool Active;
      Window* ParentWindow;
      ElementStyle Style;
      std::map<std::string, ActionType> Actions;
      virtual void SetActualPosition(int XPos, int YPos)=0;
   };
}
