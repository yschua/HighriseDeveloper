#include "StdAfx.h"
#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "AnimationSingle.h"

CAnimationSingle::CAnimationSingle(sf::Sprite* pSprite, float x, float y )
{
   m_X = x;
   m_Y = y;
   m_pCamera = new CCamera();
   m_pSprite = pSprite;
}

CAnimationSingle::~CAnimationSingle(void)
{
   // pass
}

void CAnimationSingle::Draw()
{
   m_pCamera->DrawSprite( m_pSprite );
}
