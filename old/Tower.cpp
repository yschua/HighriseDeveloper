#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Camera.h"
#include "Level.h"
#include "Person.h"
#include "AnimationSingle.h"
#include "FloorSpace.h"
#include "Map.h"
#include "Tower.h"
//from buildings import level

CTower::CTower()
{
//   m_levels = {}
//   m_people = []
   m_Pop = 0;
//   m_num_levels = num_levels
//   m_Map = NULL;
}

CTower::~CTower()
{
   for each ( CLevel* levels in m_Levels )
      delete levels;
   for each ( CPerson* person in m_People )
      delete person;
}

void CTower::Update( float dt)
{
   for each ( CLevel* level in m_Levels )
      level->Update (dt);
   for each ( CPerson* person in m_People )
      person->Update (dt);
}
void CTower::Draw( )
{
   for each ( CLevel* level in m_Levels )
      level->Draw ();
   for each ( CPerson* person in m_People )
      person->Draw ();
}
 
void CTower::AddFloorSpace( CLevel* pLevel, CFloorSpace* pFloor )
{
   //if( not l in m_levels :
   //{
   //   m_levels[l] = level (self, l)
   //   m_levels[l].add_building (building)
   //}
   m_Levels.push_back( pLevel );
   pLevel->AddFloor( pFloor );
}