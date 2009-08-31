#include "Button.h"

namespace hr {
    namespace UI {
        Button::Button() {
            //ButtonBG.SetImage(*Gfx::GetImage("UI/Star-Empty.png"));
            ButtonText.SetText("testing!!!");
            Rect.Top = 10;
            Rect.Left = 0;
            Rect.Right = 50;
            Rect.Bottom = 30;
            ButtonBG = sf::Shape::Rectangle(Rect.Left, Rect.Top, Rect.Right, Rect.Bottom, sf::Color(200,200,200,255), 1, sf::Color(0,0,0,255));
            ButtonText.SetPosition(Rect.Left, Rect.Top);
            ButtonText.SetSize(Rect.Bottom-Rect.Top-4);
            //Update();
        }
        void Button::Draw() {
            //Gfx::Window.Draw(ButtonBG);
            //Gfx::Window.Draw(ButtonText);
        }
        void Button::Update() {
            //std::cout << "(parent ADD:" << ParentWindow << ") Left: " << ParentWindow->GetRect().Left << "\tTop: " << ParentWindow->GetRect().Top << "\n";
            ButtonBG.SetPosition(Rect.Left+ParentWindow->GetRect().Left, Rect.Top+ParentWindow->GetRect().Top-10);
            ButtonText.SetPosition(Rect.Left+ParentWindow->GetRect().Left, Rect.Top+ParentWindow->GetRect().Top);
            //Button
        }
        void Button::Activate() {
            if (!Active) {
                ButtonBG.SetColor(Style.ActiveColor);
                ButtonText.SetColor(Style.ActiveColor);
                Active = true;
            }
        }
        void Button::DeActivate() {
            if (Active) {
                ButtonBG.SetColor(Style.InActiveColor);
                ButtonText.SetColor(Style.InActiveColor);
                Active = false;
            }
        }
        void Button::SetPosition(int XPos, int YPos) {
            sf::Rect<int> NewRect;
            NewRect.Left = XPos;
            NewRect.Top = YPos;
            NewRect.Right = Rect.GetWidth()+XPos;
            NewRect.Bottom = Rect.GetHeight()+YPos;
            Rect = NewRect;
        }
        void Button::SetActualPosition(int XPos, int YPos) {

        }
        sf::Vector2i Button::GetPosition() {
            return sf::Vector2i(Rect.Left, Rect.Top);
        }
        bool Button::OnEvent(const sf::Event& Event) {
            if (Event.Type == sf::Event::MouseButtonPressed) {
                ButtonBG.SetColor(sf::Color(255,255,0,255));
                ButtonText.SetColor(sf::Color(0,255,255,255));
                //Actions["pressed"](this);
                return true;
            }
            if (Event.Type == sf::Event::MouseButtonReleased) {
                ButtonBG.SetColor(sf::Color(0,0,0,255));
                ButtonText.SetColor(sf::Color(100,100,100,255));
                //Actions["released"](this);
                //Actions["clicked"](this);
                return true;
            }
            return false;
        }
        void Button::SetSize(int XSize, int YSize) {
            Rect.Right = Rect.Left+XSize;
            Rect.Bottom = Rect.Top+YSize;
        }
        sf::Vector2i Button::GetSize() {
            return sf::Vector2i(Rect.GetWidth(), Rect.GetHeight());
        }
        const sf::Rect<int>& Button::GetRect() {
            return Rect;
        }
        bool Button::Contains(int XPos, int YPos) {
            return Rect.Contains(XPos-ParentWindow->GetRect().Left, YPos-ParentWindow->GetRect().Top);
        }
        void Button::MouseIn() {

        }
        void Button::MouseOut() {
            std::cout << "Button: MouseOut()!\n";
        }
    }
}
