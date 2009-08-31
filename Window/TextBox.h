#include "Element.h"

namespace UI
{
   class TextBox : public Element
   {
   public:
      TextBox();
      void Draw();
      void Update();
      void Activate();
      void DeActivate();
      void SetPosition(int, int);
      sf::Vector2i GetPosition();
      bool OnEvent(const sf::Event&);
      void SetSize(int, int);
      sf::Vector2i GetSize();
      const sf::Rect<int>& GetRect();
      bool Contains(int, int);
   private:
      sf::String Text;
      sf::Shape BG;
      sf::Rect<int> Rect;
   };
}
