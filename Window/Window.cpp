#include "Window.h"

namespace UI
{
   WindowStyle::WindowStyle()
   {
      Resizable = true;
      Titlebar = true;
      Activated = false;
      ActiveColor.r = 255;
      ActiveColor.g = 255;
      ActiveColor.b = 255;
      ActiveColor.a = 255;
      MouseOverColor = sf::Color(0,0,0,50);
      InActiveColor.r = 255;
      InActiveColor.g = 255;
      InActiveColor.b = 255;
      InActiveColor.a = 100;
      DisabledColor.r = 100;
      DisabledColor.g = 100;
      DisabledColor.b = 100;
      DisabledColor.a = 100;
      for (int i = 0; i < 5; i++) Padding[i] = 4;
      FontSize = 10;
      //CurrentColor = InActiveColor;
   }
   WindowStyle::~WindowStyle()
   {

   }
   Window::Window()
   {
      mpCamera = Camera::GetInstance();
      BGImgs.resize(9);
      for (unsigned int i = 0; i < BGImgs.size(); i++)
      {
          std::ostringstream Name;
          Name << "window/BG" << i << ".png";
          //sf::Sprite ToCopy;
          std::cout << "size: " << BGImgs.size() << '\n';
//          BGImgs.at(i).SetImage(*Gfx::GetImage(Name.str()));
          // TODO crate the BG plane
      }
      std::cout << "Done loading images!\n";
      Rect.Top = 200;
      Rect.Left = 200;
      Rect.Bottom = 300;
      Rect.Right = 300;
      InsideRect.Top = Rect.Top+Style.Padding[0];
      InsideRect.Left = Rect.Left+Style.Padding[2];
      InsideRect.Right = Rect.Right-Style.Padding[3];
      InsideRect.Bottom = Rect.Bottom-Style.Padding[4];
      Disabled = false;
      Resized = true;
      Resizing = false;
      Moving = false;
      Activated = false;
      MouseOver = false;
      Title.SetText("Untitled Window");
      Title.SetSize(Style.FontSize);
      Update();
   }
   Window::~Window()
   {

   }
   Window Window::operator=(const Window& CopyFrom)
   {
      // TODO: Implement it!
      // Need to change the ParentWindow pointer of all
      // child controls ("elements"), and copy the contents
      // of this class.
      return *(new Window);
   }
   void Window::SetStyle(WindowStyle NewStyle)
   {
      Style = NewStyle;
   }
   WindowStyle Window::GetStyle()
   {
      return Style;
   }
   void Window::SetCaption(std::string NewCaption)
   {
      Title.SetText(NewCaption);
   }
   void Window::Update()
   {
      // Don't do anything if the window is disabled
      if (Disabled) return;

      Vector2i Mouse = mpCamera->GetLocalMouse();

      if (Resizing)
      {
         if (ResizingDir.find('N') != std::string::npos)
         {
            Rect.Top += (Mouse.y-MouseStartPosition.y);
         }
         else if (ResizingDir.find('S') != std::string::npos)
         {
            Rect.Bottom += (Mouse.y-MouseStartPosition.y);
         }
         if (ResizingDir.find('E') != std::string::npos)
         {
            Rect.Right += (Mouse.x-MouseStartPosition.x);
         }
         else if (ResizingDir.find('W') != std::string::npos)
         {
            Rect.Left += (Mouse.x-MouseStartPosition.x);
         }
         if (Rect.Left >= Rect.Right) Rect.Right = Rect.Left+1;
         if (Rect.Top >= (Rect.Bottom+TitleRect.GetHeight())) Rect.Top = Rect.Bottom+TitleRect.GetHeight()+1;
         if (Rect.Bottom <= Rect.Top+TitleRect.GetHeight()) Rect.Bottom = Rect.Top+TitleRect.GetHeight()-1;
         if (Rect.Right <= Rect.Left) Rect.Right = Rect.Left-1;
         MouseStartPosition.x = Mouse.x;
         MouseStartPosition.y = Mouse.y;
         Resized = true;
      }
      if (Moving) {
         Rect.Offset(Mouse.x-MouseStartPosition.x, Mouse.y-MouseStartPosition.y);
         MouseStartPosition.x = Mouse.x;
         MouseStartPosition.y = Mouse.y;
         Resized = true;
      }
      if (Resized) {
         // Resize the images to fill the space
         BGImgs.at(1).Resize(Rect.GetWidth()-(BGImgs.at(0).GetSize().x+BGImgs.at(2).GetSize().x), BGImgs.at(1).GetSize().y);
         BGImgs.at(3).Resize(BGImgs.at(3).GetSize().x, Rect.GetHeight()-(BGImgs.at(0).GetSize().y+BGImgs.at(6).GetSize().y));
         BGImgs.at(4).Resize(Rect.GetWidth()-(BGImgs.at(3).GetSize().x+BGImgs.at(5).GetSize().x), Rect.GetHeight()-(BGImgs.at(1).GetSize().y+BGImgs.at(7).GetSize().y));
         BGImgs.at(5).Resize(BGImgs.at(5).GetSize().x, Rect.GetHeight()-(BGImgs.at(2).GetSize().y+BGImgs.at(8).GetSize().y));
         BGImgs.at(7).Resize(Rect.GetWidth()-(BGImgs.at(6).GetSize().x+BGImgs.at(8).GetSize().x), BGImgs.at(8).GetSize().y);

         // Position all the background images in the right place
         float XOff, YOff;
         XOff = Rect.Left;
         YOff = Rect.Top;
         sf::Sprite* CurSp;
         for (int i = 0; i < 3; i++) {
            for (int j = (((i*3))); j < ((i*3)+3); j++) {
               CurSp = &BGImgs.at(j);
               CurSp->SetPosition(XOff, YOff);
               XOff += CurSp->GetSize().x;
               //std::cout << j << '\t';
            }
            YOff += CurSp->GetSize().y;
            XOff = Rect.Left;
         }

         // Update the inner rectangle
         InsideRect.Top = Rect.Top+Style.Padding[0];
         InsideRect.Left = Rect.Left+Style.Padding[2];
         InsideRect.Right = Rect.Right-Style.Padding[3];
         InsideRect.Bottom = Rect.Bottom-Style.Padding[4];

         // Reposition the title
         Title.SetPosition(InsideRect.Left, InsideRect.Top);

         // Update the title rectangle
         TitleRect.Top = InsideRect.Top;
         TitleRect.Left = InsideRect.Left;
         TitleRect.Right = InsideRect.Right;
         TitleRect.Bottom = InsideRect.Top+(Title.GetRect().Bottom-Title.GetRect().Top);
      }
      // Update the contained items
      //std::cout << "(from window ADD:" << this << ") Top: " << Rect.Top << "\tLeft: " << Rect.Left << "\n";
      //for (unsigned int i = 0; i < Items.size(); i++) {
      //    Items.at(i)->ParentWindow = this;
      //    Items.at(i)->Update();
      //}
      Items.Update();
   }

   void Window::Draw()
   {
      for (unsigned int i = 0; i < BGImgs.size(); i++)
      {
         mpCamera->Draw(BGImgs.at(i));
      }
      //std::cout << "Items size is: " << Items.size() << '\n';
      //for (unsigned int i = 0; i < Items.size(); i++) {
      //std::cout << "Drawing item: " << i << '\n';
      //    Items.at(i)->Draw();
      //}
      Items.Draw();
      mpCamera->Draw(Title);
   }

   void Window::Disable()
   {
      Disabled = true;
      DeActivate();
   }

   std::string  Window::ResizeDirection(Vector2i Mouse)
   {
      std::string& Direction = ResizingDir;
      Direction = "";
      if (Mouse.y < InsideRect.Top)
      {
         Direction += "N";
      }
      else if (Mouse.y > InsideRect.Bottom)
      {
         Direction += "S";
      }
      if (Mouse.x < InsideRect.Left)
      {
         Direction += "W";
      } else if (Mouse.x > InsideRect.Right)
      {
         Direction += "E";
      }
      //std::cout << "Direction: " << Direction << "\n";
      return Direction;
   }

   void Window::Activate()
   {
      if (!Activated)
      {
         Activated = true;
         SetColor();
      }
   }

   void Window::DeActivate()
   {
      if (Activated)
      {
         Activated = false;
         SetColor();
         //Gfx::Cur.SetType("Default");
      }
   }

   void Window::MouseIn()
   {
      if (!MouseOver)
      {
         MouseOver = true;
         SetColor();
      }
   }

   void Window::MouseOut()
   {
      //std::cout << "this is: " << this << ", MouseOver is: " << this->MouseOver << '\n';
      //if (this->MouseOver > 1) return;
      //return;
      if (MouseOver)
      {
         MouseOver = false;
         SetColor();
      }
   }

   void Window::SetColor()
   {
      sf::Color Color(0,0,0,0);
      std::cout << "Activated: " << (Activated?"true":"false")
         << "  MouseOver: " << (MouseOver?"true":"false")
         << "  Moving: " << (Moving?"true":"false")
         << "  Resizing: " << (Resizing?"true":"false")
         << "\n";
      if (Activated)
      {
         Color = Style.ActiveColor;
      }
      else
      {
         Color = Style.InActiveColor;
      }
      if (MouseOver)
      {
         Color += Style.MouseOverColor;
      }
      for (unsigned int i = 0; i < BGImgs.size(); i++)
      {
         BGImgs[i].SetColor(Color);
      }
   }

   void Window::AddItem(UI::Element* ToAdd)
   {
      ToAdd->SetParent(this);
      Items.Add(ToAdd);
      //std::cout << "Added item! New size is unknown...\n";
   }

   bool Window::OnEvent(const sf::Event& Event)
   {
      if (Disabled)
         return false;

      bool ReturnValue = false;
      Vector2i Mouse = mpCamera->GetLocalMouse();

      std::cout << "window event called! Mouse at (" << Mouse.x << ", " << Mouse.y << ")\n";
      if (Event.Type == sf::Event::MouseButtonReleased)
      {
         if (Moving || Resizing)
         {
            Moving = false;
            Resizing = false;
            ReturnValue = true;
         }
         //return false;
      }
      else if (Event.Type == sf::Event::MouseButtonPressed)
      {


         //for (unsigned int i = 0; i < Items.size(); i++) {
         //    if (Items.at(i)->GetRect().Contains(Mouse.x-Rect.Left, Mouse.y-Rect.Top)) {
         //        ActiveElement = i;
         //    }
         //}

         if (Style.Resizable)
         {
            std::string Direction = ResizeDirection(Mouse);
            if (Direction != "")
            {
               MouseStartPosition.x = Mouse.x;
               MouseStartPosition.y = Mouse.y;
               Resizing = true;
               ResizingDir = Direction;
               ReturnValue = true;
            }
         }
         // Start moving the window when the title is clicked
         if (TitleRect.Contains(Mouse.x, Mouse.y))
         {
            MouseStartPosition.x = Mouse.x;
            MouseStartPosition.y = Mouse.y;
            Moving = true;
            ReturnValue = true;
         }
      }
      else if (Event.Type == sf::Event::MouseMoved)
      {
         // If it's not inside the window, we are done here.
         if (!Rect.Contains(Event.MouseMove.X, Event.MouseMove.Y))
         {
            // Don't return if we are moving or resizing the window, as the rect may need to be adjusted.
            if (!(Resizing || Moving))
            {
               DeActivate();
               return false;
            }
         }
            //Vector2i Mouse = mpCamera->GetLocalMouse();
         /*if (Style.Resizable) {
         if (Resizing) {
         Gfx::Cur.SetType("Resize-" + ResizingDir);
         } else {
         std::string Direction = ResizeDirection(Mouse.x, Mouse.y);
         //std::cout << "HoverDirection: " << Direction << "\n";
         if (Direction == "") {
         Gfx::Cur.SetType("Default");
         } else {
         Gfx::Cur.SetType("Resize-" + Direction);
         ReturnValue = true;
         }
         }
         }*/

      }
      if (!ReturnValue) return Items.OnEvent(Event);
      //for (unsigned int i = 0; i < Items.size(); i++) {
      //    if (Items.at(i)->OnEvent(Event)) return true;
      //}
      //if (ActiveElement < Items.size()) {
      //std::cout << "ActiveElement: " << ActiveElement << '\n';
      //Items.at(ActiveElement)->OnEvent(Event);
      //}
      return ReturnValue;
   }

   const sf::Rect<int>& Window::GetRect()
   {
      return Rect;
   }

   bool Window::Contains(Vector2i Mouse)
   {
      if (Moving || Resizing) return true;
      return Rect.Contains(Mouse.x, Mouse.y);
   }
}
