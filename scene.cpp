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
#include "physics.h"
#include "routes.h"
#include "Camera.h"
#include "Window/event.h"
#include "Tower/floorBase.h"
#include "Tower/level.h"
#include "Tower/tower.h"
#include "Tower/buildStrategies.h"
#include "background.h"
#include "scene.h"

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
      bResult = true;
      break;

   case HR_PlaceApartment:
      mpBuildStrategy = new BuildApartmentStategy();
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
Scene::Update (float dt)
{
   std::cout << "Scene Update method called but it was not implemented" << std::endl;
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

void Scene::Hit( int hit, Vector2i Scene )  // taking a mouse hit, send it through geometry to see what we hit
{
   if( this->mpBuildStrategy )
   {
      std::vector<Tower *>::iterator iTower;
      for (iTower = mTowers.begin (); iTower != mTowers.end (); iTower++)
      {
         Tower* pTower = (*iTower);
         Level* pLevel = pTower->FindLevel (hit);
         if( pLevel )
         {
            Camera* pCam = Camera::GetInstance();
            int x = pCam->RenderFramework( this, Scene, pLevel->GetLevel());
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
      if( pFS )
      {
         std::cout << "Mouse on Level: " << pFS->GetLevel() << " FloorSpace ID: " << hit << std::endl;
      }
      else
      {
         std::cout << "Mouse landed on an unresgister object (BUG)" << " Level ID: " << hit  << std::endl;
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