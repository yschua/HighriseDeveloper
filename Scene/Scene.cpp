/*   This file is part of Highrise Developer.
 *
 *   Highrise Developer is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Highrise Developer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Highrise Developer.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <iostream>
#include <list>
#include "../Root/Physics.h"
#include "../Tower/Routes.h"
#include "../Graphics/Camera.h"
#include "../Window/Event.h"
#include "../Tower/FloorBase.h"
#include "../Tower/Level.h"
#include "../Tower/Tower.h"
#include "../Tower/BuildStrategies.h"
#include "Background.h"
#include "Scene.h"

//using namespace Gfx;
Scene::Scene ()
{
   mpBackground = NULL;
   mpBuildStrategy = NULL;
}

Scene::~Scene ()
{
}

void
Scene::AddTower (Tower* pTower)
{
   mTowers.push_back (pTower);   // only saved here for drawing
}

bool
Scene::SelectTool (int toolID)
{
   bool bResult = false;
   switch (toolID)
   {
   case HR_PlaceOffice:
      mpBuildStrategy = new BuildOfficeStategy();
      mpBuildStrategy->ShowGhostBuild (mTowers[0]);
      bResult = true;
      break;

   case HR_PlaceApartment:
      mpBuildStrategy = new BuildApartmentStategy();
      mpBuildStrategy->ShowGhostBuild (mTowers[0]);
      bResult = true;
      break;

   case HR_PlaceStairs:
      mpBuildStrategy = new BuildStairStategy();
      mpBuildStrategy->ShowGhostBuild (mTowers[0]);
      bResult = true;
      break;
   }
   return bResult;
}

void
Scene::SetBG (Background* pBG)
{
   mpBackground = pBG;
}

void
Scene::Update (float dt, int timeOfDay)
{
   mpBackground->Update(timeOfDay);
}

void
Scene::Draw ()
{
   mpBackground->Draw();
   std::vector<Tower *>::iterator iTower;
   for (iTower = mTowers.begin (); iTower != mTowers.end (); iTower++)
   {
      (*iTower)->Draw( );
   }
}

void Scene::RenderFramework (int level)
{
   bool bLevelsOnly = (this->mpBuildStrategy==NULL) ? false : true;
   std::vector<Tower *>::iterator iTower;
   for (iTower = mTowers.begin (); iTower != mTowers.end (); iTower++)
   {
      if (level==0)
      {
         (*iTower)->DrawFramework (bLevelsOnly);
      }
      else
      {
         Tower* pTower = (*iTower);
         Level* pLevel = pTower->GetLevel(level);
         pLevel->DrawEmptyFramework(); // only draw empty space slection zones
      }
   }
}

void Scene::MoveGhostRoom (Vector2f& point)
{
   Camera* pCam = Camera::GetInstance();
   Vector3f vec = pCam->GetOGLPos (point);
   Tower* pTower = mTowers[0];
   pTower->GetGhostRoom().Move (vec);// asp
}

void Scene::Hit( int hit, Vector2i& Scene )  // taking a mouse hit, send it through geometry to see what we hit
{
   if( mpBuildStrategy && mpBuildStrategy->PlacingRoom() )
   {
      std::vector<Tower *>::iterator iTower;
      for (iTower = mTowers.begin (); iTower != mTowers.end (); iTower++)
      {
         Tower* pTower = (*iTower);
         Level* pLevel = pTower->FindLevel (hit);
         if( pLevel )
         {
            int x = (int)(pTower->GetGhostRoom().GetX() / 9);
            std::cout << "Mouse on Level: " << pLevel->GetLevel() << " Level ID: " << hit << std::endl;
            mpBuildStrategy->BuildHere(pTower, x, pLevel->GetLevel());
            break;
         }
         else
         {
            std::cout << "Mouse on unknown level, Level ID: " << hit << std::endl;
         }
      }
   }
   else
   {
      FloorBase* pFS = FindFloorSpace(hit);
      std::vector<Tower *>::iterator iTower;
      for (iTower = mTowers.begin (); iTower != mTowers.end (); iTower++)
      {
         Tower* pTower = (*iTower);
         Level* pLevel = pTower->FindLevel (hit);
         if( pLevel )
         {
            int x = (int)(pTower->GetGhostRoom().GetX() / 9);
            std::cout << "Mouse on Level: " << pLevel->GetLevel() << " Level ID: " << hit << std::endl;
            mpBuildStrategy->BuildHere(pTower, x, pLevel->GetLevel());
            break;
         }
         else
         {
            std::cout << "Mouse landed on an unresgister object (BUG)" << " Level ID: " << hit  << std::endl;
         }
      }
   }
}

void Scene::RegisterFloorSpace (int id, FloorBase* pFS)
{
   mFloorSpaces.insert (mFloorSpaces.end(),TypeFloorSpaceMap(id, pFS));
}

void Scene::UnregisterFloorSpace (int id, FloorBase* pFS)
{
   mFloorSpaces.erase (id);
}

FloorBase* Scene::FindFloorSpace (int id)
{
   FloorBase* pFS = NULL;
   try
   {
      TypeFloorSpaceIterator it = mFloorSpaces.find(id);
      if( !(it == mFloorSpaces.end()))
      {
         TypeFloorSpaceMap& FSM = (TypeFloorSpaceMap&)(*it);
         pFS = FSM.second;
      }
   }
   catch(...)
   {
      // find failed
   }

   return pFS;
}
