#include "TextBox.h"

#include "Window.h"

namespace hr {
    namespace UI {
        TextBox::TextBox() {
            //ButtonBG.SetImage(*Gfx::GetImage("UI/Star-Empty.png"));
            Text.SetText("testing!!!");
            Rect.Top = 10;
            Rect.Left = 0;
            Rect.Right = 50;
            Rect.Bottom = 30;
            BG = sf::Shape::Rectangle(Rect.Left, Rect.Top, Rect.Right, Rect.Bottom, sf::Color(200,200,200,255), 1, sf::Color(0,0,0,255));
            Text.SetPosition(Rect.Left, Rect.Top);
            Text.SetSize(Rect.Bottom-Rect.Top-4);
            //Update();
        }
        void TextBox::Draw() {
            //Gfx::Window.Draw(BG);
            //Gfx::Window.Draw(Text);
        }
        void TextBox::Update() {
            //std::cout << "(parent ADD:" << ParentWindow << ") Left: " << ParentWindow->GetRect().Left << "\tTop: " << ParentWindow->GetRect().Top << "\n";
            //BG.SetPosition(Rect.Left+ParentWindow->GetRect().Left, Rect.Top+ParentWindow->GetRect().Top);
            //Text.SetPosition(Rect.Left+ParentWindow->GetRect().Left, Rect.Top+ParentWindow->GetRect().Top);
            //Button
        }
        void TextBox::Activate() {
            if (!Active) {
                BG.SetColor(Style.ActiveColor);
                Text.SetColor(Style.ActiveColor);
                Active = true;
            }
        }
        void TextBox::DeActivate() {
            if (Active) {
                BG.SetColor(Style.InActiveColor);
                Text.SetColor(Style.InActiveColor);
                Active = false;
            }
        }
        void TextBox::SetPosition(int XPos, int YPos) {
            sf::Rect<int> NewRect;
            NewRect.Left = XPos;
            NewRect.Top = YPos;
            NewRect.Right = Rect.GetWidth()+XPos;
            NewRect.Bottom = Rect.GetHeight()+YPos;
            Rect = NewRect;
        }
        sf::Vector2i TextBox::GetPosition() {
            return sf::Vector2i(Rect.Left, Rect.Top);
        }
        bool TextBox::OnEvent(const sf::Event& Event) {
            if (Event.Type == sf::Event::MouseButtonPressed) {
                // TODO: Select a portion of the text
                //BG.SetColor(sf::Color(255,255,0,255));
                //Text.SetColor(sf::Color(0,255,255,255));
                //Actions["pressed"](this);
                return true;
            }
            if (Event.Type == sf::Event::MouseButtonReleased) {
                BG.SetColor(sf::Color(0,0,0,255));
                Text.SetColor(sf::Color(100,100,100,255));
                //Actions["released"](this);
                //Actions["clicked"](this);
                return true;
            }
            return false;
        }
        void TextBox::SetSize(int XSize, int YSize) {
            Rect.Right = Rect.Left+XSize;
            Rect.Bottom = Rect.Top+YSize;
        }
        sf::Vector2i TextBox::GetSize() {
            return sf::Vector2i(Rect.GetWidth(), Rect.GetHeight());
        }
        const sf::Rect<int>& TextBox::GetRect() {
            return Rect;
        }
        bool TextBox::Contains(int XPos, int YPos) {
            return Rect.Contains(XPos-ParentWindow->GetRect().Left, YPos-ParentWindow->GetRect().Top);
        }
    }
}
