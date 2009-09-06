#include "Element.h"

namespace UI
{
   class TextBox : public Element
   {
   private:
      sf::String* mpText;
      sf::Shape BG;
      sf::Rect<int> mRect;

   public:
      TextBox();
      virtual ~TextBox();

      void Draw();
      void Update();
      void SetPosition(int, int);
      void SetActualPosition(int, int);
      void SetText( const char* pszText )
      {
         mpText = new sf::String(pszText);
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
      void Activate();
      void DeActivate();

   };
}
