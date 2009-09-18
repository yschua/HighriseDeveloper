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


//#ifdef WIN32
#include <iostream>
#include "physics.h"
#include "routes.h"
#include "Window/event.h"
#include "Tower/floorBase.h"
#include "Tower/tower.h"
#include "Tower/buildStrategies.h"
#include "background.h"
#include "scene.h"

//#else
//#include "../highrisedev.h"
//#endif

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

void Scene::RenderFramework()
{
   int lastNo = 1;
   std::vector<Tower *>::iterator iTower;
   for (iTower = mTowers.begin (); iTower != mTowers.end (); iTower++)
   {
      (*iTower)->DrawFramework ();
   }
}

#define BUFFER_LENGTH 64   // max click hits we expect but we might get 2

void Scene::Hit( int xPos, int yPos, float fAspect )  // taking a mouse hit, send it through geometry to see what we hit
{
   // Space for selection buffer
   GLuint selectBuff[BUFFER_LENGTH];
   
   // Hit counter and viewport storeage
   GLint hits, viewport[4];
   
   // Setup selection buffer
   glSelectBuffer(BUFFER_LENGTH, selectBuff);
   
   // Get the viewport
   glGetIntegerv(GL_VIEWPORT, viewport);
   
   // Switch to projection and save the matrix
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   
   // Change render mode
   glRenderMode(GL_SELECT);
   
   // Establish new clipping volume to be unit cube around
   // mouse cursor point (xPos, yPos) and extending two pixels
   // in the vertical and horzontal direction
   glLoadIdentity();
   gluPickMatrix(xPos, viewport[3] - yPos, 1, 1, viewport);
   
   // Apply perspective matrix 
   gluPerspective(90.0f, fAspect, 1.0f, 1000.f);		// Calculate The Aspect Ratio Of The Window
   
   // Draw the scene
   RenderFramework();
   
   // Collect the hits
   hits = glRenderMode(GL_RENDER);
   
   // Restore the projection matrix
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   
   // Go back to modelview for normal rendering
   glMatrixMode(GL_MODELVIEW);
   
   // If a single hit occured, display the info.
   GLuint nHit = -1;
   if(hits == 1)
   {
//      MakeSelection(selectBuff[3]);
      if(nHit != selectBuff[3])
      {
         nHit = selectBuff[3]; // ok what did we hit
      }
   }
   
//   glutPostRedisplay();
}