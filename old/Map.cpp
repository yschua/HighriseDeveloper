//from PySFML import sf
//from animation import animation_single
//import camera
//import image
#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "Tower.h"
#include "Image.h"
#include "AnimationSingle.h"
#include "Map.h"

using namespace sf;

CMap::CMap( CTower* pTower, int world_x, int world_y )
{
   m_pCamera = new CCamera();
   m_WorldX = world_x;
   m_WorldY = world_y;
   m_World_prop = (float)(200.0 / world_x);
   m_Aspect = (float (world_y) / float(world_x));
   m_X = 200;
   m_Y = (int)(m_Aspect * 200.0);
   int levels = pTower->get_Levels();
   m_LevelHeight = (m_Y / levels);
   m_MiniMap = new sf::Image( m_X, m_Y, sf::Color (0,0,0,0));
   m_MiniMapSprite = new sf::Sprite( *m_MiniMap, sf::Vector2f(5, 65), sf::Vector2f(0,0), 0.0, sf::Color (0,0,0,0) );
   DrawMap ();
   m_pTower = pTower;
   m_pTower->SetMap( this );
   cam_x = m_pCamera->get_CamX();
   cam_y = m_pCamera->get_CamY();
   m_cambox_x = (int)(cam_x * m_World_prop);
   m_cambox_y = (int)(cam_y * m_World_prop);
   m_pGround = new CAnimationSingle( CImage::Load ( "mini_ground.png"), 0, 0);
   m_pSky = new CAnimationSingle( CImage::Load ( "mini_back.png"), 0, 0);
   m_GroundSize = (10 * m_LevelHeight);
   m_pGround->SetPosition( 5.0f, 65.0f + (float)(m_Y - m_GroundSize) );
   m_pSky->SetPosition( 5.0f, 65.0f );
   m_pGround->Resize( (float)m_X, (float)m_GroundSize );
   m_pSky->Resize( (float)m_X, (float)(m_Y - m_GroundSize) );
   m_pMiniBorder = sf::Shape::Rectangle(5.0f, 65.0f, (float)m_X + 5, (float)m_Y + 65, sf::Color (0,0,0,0), 2, sf::Color (0,0,0));
   m_pCambox = sf::Shape::Rectangle(0, 0, (float)m_cambox_x, (float)m_cambox_y, sf::Color (0,0,0,0), 2, sf::Color (255,255,255));
}
void CMap::DrawMap()
{
   sf::Color grey = sf::Color (80, 80, 80, 255);
   for each( CLevel* level in m_ClickMap )
   {
      //for each (x in range (m_world_x) )
      //{
      //   if( ! (m_click_map[level][x] == NULL) )
      //   {
      //      x_pixel = x * m_world_prop;
      //      y_pixel =  m_y - (level * m_level_height) - m_ground_size;
      //      for each (i in range (m_level_height + 1) )
      //      {
      //         m_MiniMap.SetPixel (x_pixel, y_pixel + i, grey);
      //      }
      //   }
      //}
   }
}
void CMap::SetCallback( CLevel* level, float x, float x2, CObjectBase* object )
{
   int world_x = m_pCamera->get_WorldX();
   int world_y = m_pCamera->get_WorldY();
   //if( !( level in m_click_map ))
   //{
   //   m_click_map[level] = [None for y in range (world_x)];
   //}

   //for each( i in range (x, x2) )
   //{
   //   m_click_map[level][i] = object;
   //}
}

CLevel* CMap::WorldClick( int x, int y, long cargo_2)
{
   int level = (y / 36) + 1;
   try
   {
      CLevel* pLevel = m_ClickMap[level];//[x]
      return pLevel;
   }
   catch( ... )
   {
      return NULL;
   }
}
void CMap::Click(int x, int y)
{
   m_pCamera->Center( (int)((float)(x - 5)/ m_World_prop), (int)((float)(y - 65)/m_World_prop) );
}
void CMap::Resize ( int x, int y)
{
   m_cambox_x = (int)(x * m_World_prop);
   m_cambox_y = (int)(y * m_World_prop);
}
void CMap::DrawMinimap( )
{
   int pos_x = m_pCamera->get_CamPosX();
   int pos_y = m_pCamera->get_CamPosY ();
   m_pCamera->DrawSpriteIgnore (m_pSky->GetSprite());
   m_pCamera->DrawSpriteIgnore (m_pGround->GetSprite());
//   m_pCamera->DrawSpriteIgnore (m_pMiniBorder );
   m_pCambox.SetPosition (5 + (pos_x * m_World_prop), 65 + (pos_y * m_World_prop));
   m_pCamera->DrawSpriteIgnore (m_MiniMapSprite);
//   m_pCamera->DrawSpriteIgnore (m_pCambox);
}