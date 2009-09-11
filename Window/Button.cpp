// Button

#include "../Types/Vector2.h"
#include "../Camera.h"
#include "Button.h"

namespace UI
{
   class Window;
   Button::Button()
   {
      //ButtonBG.SetImage(*Gfx::GetImage("UI/Star-Empty.png"));
      mRect.Top = 10;
      mRect.Left = 0;
      mRect.Right = 50;
      mRect.Bottom = 30;
      mButtonBG = sf::Shape::Rectangle(mRect.Left, mRect.Top, mRect.Right, mRect.Bottom, sf::Color(200,200,200,255), 1, sf::Color(0,0,0,255));
      mpButtonText = new sf::String("Le Bouton" );
      mpButtonText->SetPosition(mRect.Left, mRect.Top);
      mpButtonText->SetSize(mRect.Bottom-mRect.Top-4);
      mpButtonText->SetText("testing!!!");
      //Update();
   }
   Button::~Button()
   {
      delete mpButtonText;
   }

   void Button::Draw()
   {
      //Gfx::Window.Draw(ButtonBG);
      //Gfx::Window.Draw(ButtonText);
   }

   void Button::Update()
   {
      //std::cout << "(parent ADD:" << ParentWindow << ") Left: " << ParentWindow->GetRect().Left << "\tTop: " << ParentWindow->GetRect().Top << "\n";
      mButtonBG.SetPosition(mRect.Left+ParentWindow->GetRect().Left, mRect.Top+ParentWindow->GetRect().Top-10);
      mpButtonText->SetPosition(mRect.Left+ParentWindow->GetRect().Left, mRect.Top+ParentWindow->GetRect().Top);
      //Button
   }

   void Button::Activate()
   {
      if (!Active)
      {
         mButtonBG.SetColor(Style.ActiveColor);
         mpButtonText->SetColor(Style.ActiveColor);
         Active = true;
      }
   }

   void Button::DeActivate()
   {
      if (Active)
      {
         mButtonBG.SetColor(Style.InActiveColor);
         mpButtonText->SetColor(Style.InActiveColor);
         Active = false;
      }
   }

   void Button::SetPosition(int XPos, int YPos)
   {
      sf::Rect<int> NewRect;
      NewRect.Left = XPos;
      NewRect.Top = YPos;
      NewRect.Right = mRect.GetWidth()+XPos;
      NewRect.Bottom = mRect.GetHeight()+YPos;
      mRect = NewRect;
   }

   void Button::SetActualPosition(int XPos, int YPos)
   {

   }

   sf::Vector2i Button::GetPosition()
   {
      return sf::Vector2i(mRect.Left, mRect.Top);
   }

   bool Button::OnEvent(const sf::Event& Event)
   {
      if (Event.Type == sf::Event::MouseButtonPressed)
      {
         mButtonBG.SetColor(sf::Color(255,255,0,255));
         mpButtonText->SetColor(sf::Color(0,255,255,255));
         //Actions["pressed"](this);
         return true;
      }
      if (Event.Type == sf::Event::MouseButtonReleased)
      {
         mButtonBG.SetColor(sf::Color(0,0,0,255));
         mpButtonText->SetColor(sf::Color(100,100,100,255));
         //Actions["released"](this);
         //Actions["clicked"](this);
         return true;
      }
      return false;
   }

   void Button::SetSize(int XSize, int YSize)
   {
      mRect.Right = mRect.Left+XSize;
      mRect.Bottom = mRect.Top+YSize;
   }

   sf::Vector2i Button::GetSize()
   {
      return sf::Vector2i(mRect.GetWidth(), mRect.GetHeight());
   }

   const sf::Rect<int>& Button::GetRect()
   {
      return mRect;
   }
   bool Button::Contains(Vector2i Mouse)
   {
      return mRect.Contains(Mouse.x-ParentWindow->GetRect().Left, Mouse.y-ParentWindow->GetRect().Top);
   }

   void Button::MouseIn()
   {

   }

   void Button::MouseOut()
   {
      std::cout << "Button: MouseOut()!\n";
   }
}
