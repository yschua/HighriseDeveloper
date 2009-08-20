#include "Person.h"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Camera.h"
#include "Animation.h"
#include "AnimationSingle.h"
#include "Tower.h"
#include "FloorSpace.h"

CFloorSpace::CFloorSpace( sf::Sprite* pSprite, CTower* pTower, float x, float x2, float y )
{
   m_Level = 1;
   m_pTower = pTower;
   m_X = x;
   m_X2 = x2;
   m_pCamera = new CCamera();
   m_pLevel = new CLevel( m_Level, m_pCamera, pTower ); // 1 Star (boring)
   m_WorldX = (float)m_pCamera->get_WorldX();
   m_WorldY = (float)m_pCamera->get_WorldY();
   m_Y = ( m_WorldY - 360) - ( m_Level * 36);
   m_Time = 0;
   //m_states = {}
   //m_animations = {}
   m_CurrentState = 0;//None
   m_pCurrentAnimation = 0;//None
   m_pTower->AddFloorSpace( m_pLevel, this );
   m_pTower->SetMapCallBack( m_pLevel, m_X, m_X2, this );
}

CFloorSpace::~CFloorSpace(void)
{
}


void CFloorSpace::Update( float state )
{
   m_CurrentState = state;
   if( m_pCurrentAnimation )
   {
      m_pCurrentAnimation->Update(state);
   }
}

void CFloorSpace::Draw()
{
   if( m_pCurrentAnimation )
   {
      m_pCurrentAnimation->Draw ();
   }
};
