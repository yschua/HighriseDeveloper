//import camera
//import image
//from animation import tiler_noclip, animation_single
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "Image.h"
#include "Tiler.h"
#include "TilerNoClip.h"
#include "AnimationSingle.h"
#include "Background.h"
            
CBackground::CBackground( float bg_x, float bg_y )
{
   m_X = bg_x;
   m_Y = bg_y;
   sf::Sprite* pImage = CImage::Load ("back.png");
   m_pBackground = new CAnimationSingle( pImage, bg_x, bg_y );
   m_pGround = new CTilerNoClip( CImage::Load ("ground.png" ), 0, bg_x, bg_y - 360);
   m_pBuildings = new CTilerNoClip( CImage::Load("buildings.png"), 0, bg_x, bg_y - 360 - 55);
}

CBackground::~CBackground()
{
   try
   {
      delete m_pBackground;
      delete m_pGround;
      delete m_pBuildings;
   }
   catch( ... )
   {
      std::cout << "CBackground DTOR: Error freeing local members!";
      // aler
   }

}

void CBackground::Draw()
{
   m_pBackground->Draw();
   m_pGround->Draw();
   m_pBuildings->Draw();
};
