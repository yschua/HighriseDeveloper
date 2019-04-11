//from PySFML import sf
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "AnimationSingle.h"
#include "Camera.h"
//#include "Tower.h"
//#include "Building.h"
//#include "Tower.h"
CCamera::CCamera()
{
   //m___dict__ = m___shared_state   ** Ownage
}

CCamera::~CCamera()
{
   //delete m___dict__ = m___shared_state
}

void CCamera::Setup( int cam_x, int cam_y, int world_x, int world_y, string caption)
{
   //  m___dict__ = m___shared_state
   //   m_pScreen = new sf::RenderWindow( new sf::VideoMode(cam_x, cam_y), caption, sf.Style.Close)
   m_X = cam_x;
   m_Y = cam_y;
   m_VX = 0.0;
   m_VY = 0.0;
   m_AX = 0.0;
   m_AY = 0.0;
   m_WorldX = world_x;
   m_WorldY = world_y;
   m_PosX = 0;
   m_PosY = 0;
   //m_pScreen->SetFramerateLimit (60);
}


void CCamera::DrawSprite( sf::Sprite* pSprite )
{
   m_pSprite->SetPosition( pSprite->GetPosition().x - m_PosY, pSprite->GetPosition().y - m_PosY );
//   m_pScreen.Draw( pSprite);
}

void CCamera::DrawSpriteIgnore( sf::Sprite* pSprite) 
{
   m_pSprite->SetPosition( pSprite->GetPosition().x, pSprite->GetPosition().y );
//   m_pScreen.Draw (sprite);
}

void CCamera::DrawShapeIgnore( sf::Shape& shape)
{
//   m_pScreen.Draw (shape);
}

int CCamera::get_Events ( sf::Event& event )
{
//   return m_pScreen.GetEvent (event);
   return 0;
}

void CCamera::Resize ( int x, int y)
{
//   m_pScreen.SetSize ( int x , int y);
}
int CCamera::get_Input()
{
//   return m_pScreen.GetInput ();
   return 0;
}
void CCamera::DrawTextIgnore ( sf::String text)
{
//   m_pScreen.Draw (text);
}

void CCamera::SetPosition( int x, int y)
{
   if( x != 0 )
      m_PosX = x;
   if( y != 0 )
      m_PosY = y;
}

void CCamera::Center( int new_x, int new_y )
{
   m_PosX = new_x - (m_X / 2);
   m_PosY = new_y - (m_Y / 2);
}

void CCamera::set_Velocity( int x, int y )
{
   if( x != 0 )
      m_VX = (float)x;
   if( y != 0 )
      m_VY = (float)y;
}

void CCamera::set_Acceleration( int x, int y)
{
   if( x != 0 )
      m_AX = (float)x;
   if( y != 0 )
      m_AY = (float)y;
}

void CCamera::Clear ()
{
//   m_pScreen.Clear ();
}

void CCamera::Update( int state ) 
{
   float dt_secs = float (state) / 1000;
   m_PosX += (int)(m_VX * dt_secs);
   m_PosY += (int)(m_VY * dt_secs);
   m_VX += m_AX * dt_secs;
   m_VY += m_AY * dt_secs;
   if( m_VX > -10 && m_VX < 10)
   {
      m_VX = 0;
      m_AX = 0;
   }
   if (m_VY > -10 && m_VY < 10)
   {
      m_VY = 0;
      m_AY = 0;
   }
   if( m_PosX < 0 )
   {
      m_PosX = 0;
      m_VX = 0;
      m_AX = 0;
   }
   if( m_PosY < 0 )
   {
      m_PosY = 0;
      m_VY = 0;
      m_AY = 0;
   }
   if( m_PosX > m_WorldX - m_X )
   {
      m_PosX = m_WorldX - m_X;
      m_VX = 0;
      m_AX = 0;
   }
   if( m_PosY > m_WorldY - m_Y )
   {
      m_PosY = m_WorldY - m_Y;
      m_VY = 0;
      m_AY = 0;
   }
}

void CCamera::Display ()
{
//   m_pScreen.Display ()
}

void CCamera::Move( int x, int y)
{
   if( x != 0 )
      m_PosX += x;
   if( y != 0 )
      m_PosY += y;
}