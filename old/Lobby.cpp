#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ObjectBase.h"
#include "Level.h"
#include "Camera.h"
#include "AnimationSingle.h"
#include "Tower.h"
#include "Tiler.h"
#include "Lobby.h"

CLobby::CLobby( CTower* pTower, float x, float x2, float y )
:  CFloorSpace( new sf::Sprite(), pTower, x, 0, x2 ) // always level 0
{
//   m_LobbyTiles = new CTiler (image.load ("lobby.png"), x, x2, y);
//   m_awn_right = new CAnimationSingle( image.load ("awn_right.png"));
//   m_awn_left = new CAnimationSingle( image.load ("awn_left.png"));
   DoCalcs();
}

CLobby::~CLobby(void)
{
}

void CLobby::DoCalcs( )
{
//   awn_right.set_position (m_X2, m_Y);
//   awn_left.set_position (m_X - 56, m_Y);
}
 
void CLobby::Update( float dt)
{
   //pass
}


void CLobby::Draw()
{
//   m_LobbyTiles.Draw ();
//   awn_right.Draw ();
//   awn_left.Draw ();
}