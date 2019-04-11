#include <SFML/Graphics.hpp>
#include "TilerNoClip.h"
#include "Camera.h"
#include "AnimationSingle.h"

CTilerNoClip::CTilerNoClip( sf::Sprite* pSprite, float x, float x2, float y )
{
   m_pSprite = pSprite;
   m_X = x;
   m_X2 = x2;
   m_Y = y;
   m_ImageSizeX = m_pSprite->GetSize().x;
   m_ImageSizeY = m_pSprite->GetSize().y;
   m_tiled_num = int((x2 - x) / m_ImageSizeX) + 1;
   m_pCamera = new CCamera();
   for( int idx = 0; idx < m_tiled_num; ++idx )
   {
      CAnimationSingle* pAS_Sprite = new CAnimationSingle( pSprite, x, y );
      m_Sprites.push_back( pAS_Sprite );
      pAS_Sprite->SetPosition( m_X + (idx * m_ImageSizeX ), m_Y );
   }
}

CTilerNoClip::~CTilerNoClip(void)
{
}

void CTilerNoClip::Resize( float x, float x2 )
{
   if( x != 0.0 )
      m_X = x;
   if( x2 != 0.0 )
      m_X2 = x2;

   unsigned int tiled_num_new = (unsigned int)((x2 - x) / m_ImageSizeX) + 1;
   if( m_Sprites.size() > tiled_num_new )
   {
      while( m_Sprites.size() > tiled_num_new )
      {
         m_Sprites.pop_back();
      }
   }
   else
   {
      for( int idx = 0; idx < m_tiled_num; ++idx )
      {
         CAnimationSingle* pAS_Sprite = new CAnimationSingle( m_pSprite, 0, 0  );
         m_Sprites.push_back( pAS_Sprite );
         pAS_Sprite->SetPosition( m_X + (idx * m_ImageSizeX ), m_Y );
      }
   }
}
void CTilerNoClip::Draw()
{
   for each (CAnimationSingle *pSprite in m_Sprites)
   {
      m_pCamera->DrawSprite( pSprite->GetSprite() );
   }
}