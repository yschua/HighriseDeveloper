// Text

#include <iostream>

#include "../Types/Vector2.h"
#include "../Camera.h"
#include "TextBox.h"

#include "Window.h"

namespace UI
{
   TextBox::TextBox()
   {
      //ButtonBG.SetImage(*Gfx::GetImage("UI/Star-Empty.png"));
      mRect.Top = 10;
      mRect.Left = 0;
      mRect.Right = 50;
      mRect.Bottom = 30;
      BG = sf::Shape::Rectangle(mRect.Left, mRect.Top, mRect.Right, mRect.Bottom, sf::Color(200,200,200,255), 1, sf::Color(0,0,0,255));
      mpText = new sf::String("Le Type");
      mpText->SetPosition(mRect.Left, mRect.Top);
      mpText->SetSize(mRect.Bottom-mRect.Top-4);
      mpText->SetText("testing!!!");
      //Update();
   }

   TextBox::~TextBox()
   {
      delete mpText;
   }

   void TextBox::Draw()
   {
      //Gfx::Window.Draw(BG);
      //Gfx::Window.Draw(Text);
   }

   void TextBox::Update()
   {
      //std::cout << "(parent ADD:" << ParentWindow << ") Left: " << ParentWindow->GetRect().Left << "\tTop: " << ParentWindow->GetRect().Top << "\n";
      //BG.SetPosition(Rect.Left+ParentWindow->GetRect().Left, Rect.Top+ParentWindow->GetRect().Top);
      //Text.SetPosition(Rect.Left+ParentWindow->GetRect().Left, Rect.Top+ParentWindow->GetRect().Top);
      //Button
   }
   void TextBox::Activate()
   {
      if (!Active)
      {
         BG.SetColor(Style.ActiveColor);
         mpText->SetColor(Style.ActiveColor);
         Active = true;
      }
   }

   void TextBox::DeActivate()
   {
      if (Active) {
         BG.SetColor(Style.InActiveColor);
         mpText->SetColor(Style.InActiveColor);
         Active = false;
      }
   }

   void TextBox::SetPosition(int XPos, int YPos)
   {
      sf::Rect<int> NewRect;
      NewRect.Left = XPos;
      NewRect.Top = YPos;
      NewRect.Right = mRect.GetWidth()+XPos;
      NewRect.Bottom = mRect.GetHeight()+YPos;
      mRect = NewRect;
   }

   void TextBox::SetActualPosition(int XPos, int YPos)
   {

   }

   sf::Vector2i TextBox::GetPosition()
   {
      return sf::Vector2i(mRect.Left, mRect.Top);
   }

   bool TextBox::OnEvent(const sf::Event& Event)
   {
      if (Event.Type == sf::Event::MouseButtonPressed)
      {
         // TODO: Select a portion of the text
         //BG.SetColor(sf::Color(255,255,0,255));
         //Text.SetColor(sf::Color(0,255,255,255));
         //Actions["pressed"](this);
         return true;
      }
      if (Event.Type == sf::Event::MouseButtonReleased)
      {
         BG.SetColor(sf::Color(0,0,0,255));
         mpText->SetColor(sf::Color(100,100,100,255));
         //Actions["released"](this);
         //Actions["clicked"](this);
         return true;
      }
      return false;
   }

   void TextBox::SetSize(int XSize, int YSize)
   {
      mRect.Right = mRect.Left+XSize;
      mRect.Bottom = mRect.Top+YSize;
   }

   sf::Vector2i TextBox::GetSize()
   {
      return sf::Vector2i(mRect.GetWidth(), mRect.GetHeight());
   }

   const sf::Rect<int>& TextBox::GetRect()
   {
      return mRect;
   }

   bool TextBox::Contains(Vector2i Mouse)
   {
      return mRect.Contains(Mouse.x-ParentWindow->GetRect().Left, Mouse.y-ParentWindow->GetRect().Top);
   }
   void TextBox::MouseIn()
   {

   }

   void TextBox::MouseOut()
   {
      std::cout << "Button: MouseOut()!\n";
   }
}
