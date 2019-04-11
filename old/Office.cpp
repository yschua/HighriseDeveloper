#include <vector>
#include <iostream>
// these are for Randomization used for testing
#include <math.h>
#include <stdlib.h>
//
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Camera.h"
#include "Tower.h"
#include "AnimationSingle.h"
#include "Office.h"

COffice::COffice( CTower* pTower, float x, float level, float x2 )
:  CFloorSpace( new sf::Sprite(), pTower, x, level, x + 72 )
{
   //m_states['unoccupied_day'] = office.unoccupied_day
   //m_states['occupied_day'] = office.occupied_day
   //m_animations['unoccupied_day'] = animation ()
   //m_animations['unoccupied_day'].load ('office.ini', 'unoccupied_day')
   //m_animations['occupied_day'] = animation ()
   //m_animations['occupied_day'].load ('office.ini', 'occupied_day')
   //m_animations['unoccupied_day'].set_position (m_x, m_y)
   //m_animations['occupied_day'].set_position (m_x, m_y)
   //m_current_state = m_occupied_day
   //m_current_animation = m_animations['occupied_day']
}

COffice::~COffice(void)
{
}

void COffice::UnoccupiedDay( float dt )
{
   dt += 1;
   if( dt > rand() * 30 + 200)
   {
//      m_CurrentState = m_occupied_day;
//      m_CurrentAnimation = m_animations['occupied_day'];
      m_DT = 0;
   }
}

void COffice::OccupiedDay( float dt )
{
   dt += 1;
   if( dt > rand() * 30 + 2000 )
   {
//      m_CurrentState = m_unoccupied_day;
//      current_animation = m_animations['unoccupied_day'];
      m_DT = 0;
   }
}
