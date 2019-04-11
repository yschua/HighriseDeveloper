#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "AnimationSingle.h"
#include "Tiler.h"

CTiler::CTiler( sf::Sprite* pSprite, float x, float x2, float y )
{
   m_pSprite = pSprite;
   m_X = x;
   m_X2 = x2;
   m_Y = y;
   m_ImageSizeX = m_pSprite->GetSize().x;
   m_ImageSizeY = m_pSprite->GetSize().y;
   unsigned int tiled_num = (unsigned int)( (x2 - x) / m_ImageSizeX );
   m_pCamera = new CCamera();
   float fPart = ( tiled_num * m_ImageSizeX ) + m_X;
   //sf::Rect<sf::IntRect> part_rect = 
   sf::IntRect part_rect(0, 0, (int)(m_X2 - fPart), (int)(m_ImageSizeY) );
   for( unsigned int idx = 0; idx < tiled_num; ++idx )
   {
      CAnimationSingle* pAS_Sprite = new CAnimationSingle( pSprite, x, y );
      m_Sprites.push_back( pAS_Sprite );
      pAS_Sprite->SetPosition( m_X + (idx * m_ImageSizeX ), m_Y );
   }
   CAnimationSingle* pAS_Sprite = m_Sprites[m_Sprites.size()-1];
   pAS_Sprite->SetSubRect( part_rect);
}

CTiler::~CTiler(void)
{
}

void CTiler::Draw( )
{
   for each ( CAnimationSingle* pSprite in m_Sprites )
   {
      m_pCamera->DrawSprite( pSprite->GetSprite() );
   }
}
