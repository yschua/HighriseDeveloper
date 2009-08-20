#pragma once
class CCamera;

class CAnimationSingle
{
   float m_X;
   float m_Y;
   CCamera* m_pCamera;
   sf::Sprite* m_pSprite;

public:
   CAnimationSingle( sf::Sprite* pSprite, float x, float y  );
   ~CAnimationSingle(void);

   // properties
   sf::Sprite* GetSprite() { return m_pSprite; };

   //implementation
   void SetPosition( float x, float y )
   {
      m_X = x;
      m_Y = y;
   }
   void Draw();
   void SetImage( sf::Image& rImage )
   {
      m_pSprite->SetImage(rImage);
   }
   void SetSubRect( sf::IntRect& rect )
   {
      m_pSprite->SetSubRect( rect );
   }
   void Resize( float x, float y )
   {
      m_pSprite->Resize( x, y );
   }
};
