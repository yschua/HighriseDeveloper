// never built this one
//from PySFML import sf
//import sys, os
//from animation import animation_single

//import image
//import camera
#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "Image.h"
#include "AnimationSingle.h"
#include "Interface.h"
using namespace sf;

CInterface::CInterface()
{
//   m_tower = tower;
   m_pCamera = new CCamera();
   m_Clock = new CAnimationSingle (CImage::Load("clock.png"), 0,0);
   m_Clock->SetPosition (0 , 0 );

   m_Stars.push_back( new CAnimationSingle( CImage::Load ("star_empty.png"), 0, 0));
   m_Stars.push_back( new CAnimationSingle( CImage::Load ("star_empty.png"), 0, 0));
   m_Stars.push_back( new CAnimationSingle( CImage::Load ("star_empty.png"), 0, 0));
   m_Stars.push_back( new CAnimationSingle( CImage::Load ("star_empty.png"), 0, 0));
   m_Stars.push_back( new CAnimationSingle( CImage::Load ("star_empty.png"), 0, 0));
   m_Font.LoadFromFile( "data\\DejaVuSans.ttf" );
   m_Text = sf::String( "Population: 0", m_Font, 11 );
   m_Text.SetPosition (65, 40);

//   m_camera = camera.camera ();
   int i = 0;
   for each( CAnimationSingle* star in m_Stars )
   {
      star->SetPosition( (float)60 + i, 0);
      i += 40;
   }
}
//    def update (self, dt, time) :
void CInterface::Update( float dt)
{
   //pass;
}
//    def set_star (self, star) :
void CInterface::SetStar( int star )
{
   CAnimationSingle* pStar = m_Stars[star];
   delete pStar;
   m_Stars[star] = new CAnimationSingle( CImage::Load ( "star.png" ), (float)60 + star*40, 0);
}
//    def draw (self) :
void CInterface::Draw()
{
   m_pCamera->DrawSpriteIgnore( m_Clock->GetSprite() );
   for each( CAnimationSingle* star in m_Stars )
   {
      m_pCamera->DrawSpriteIgnore (star->GetSprite());
   }
   m_pCamera->DrawTextIgnore( m_Text );
}