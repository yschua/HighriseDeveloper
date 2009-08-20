//from animation import animation, animation_single, tiler
//import image
//from camera import camera
//import random
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ObjectBase.h"
#include "Camera.h"
#include "AnimationSingle.h"
#include "Tower.h"
#include "FloorSpace.h"
#include "Level.h"

CLevel::CLevel( int level, CCamera* pCam, CTower* pTower )
{
   m_pCamera = pCam;
   m_WorldX = pCam->get_WorldX();
   m_WorldY = pCam->get_WorldY();
   m_X = m_WorldX;
   m_X2 = 0;
   m_Level = level;
   m_Y = (m_WorldY - 360) - (level * 36);
   m_pTower = pTower;
//      m_buildings = []
//   m_fire_escape_l = new CAnimationSingle( image.load ("fire_escape_l.png") );
//   m_fire_escape_r = new CAnimationSingle( image.load ("fire_escape_r.png") );
}

CLevel::~CLevel()
{
}

void CLevel::AddFloor( CFloorSpace* pFloor )
{
   m_FloorSpaces.push_back( pFloor );
   if( pFloor->get_X() < m_X )
   {
      m_X = (int)pFloor->get_X();
   }
   if( pFloor->get_X2() > m_X2 )
   {
      m_X2 = (int)pFloor->get_X2();
   }
//   m_fire_escape_l.set_position(m_X - 24, m_Y)
//   m_fire_escape_r.set_position(m_X2, m_Y)
}

void CLevel::Update( float dt )
{
   for each( CFloorSpace *pFloor in m_FloorSpaces )
   {
      pFloor->Update(dt);
   }
}

void CLevel::Draw()
{
   for each( CFloorSpace* pFloor in m_FloorSpaces )
   {
      pFloor->Draw( );
      if( m_Level != 1 )
      {
//         m_fire_escape_l.Draw ()
//         m_fire_escape_r.Draw ()
      }
   }
}
