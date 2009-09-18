/*This file is part of Highrise Developer.
 *
 *Highrise Developer is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.

 *Highrise Developer is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with Highrise Developer.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "resources.h"

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "physics.h"
#include "image.h"
#include "animation.h"
#include "scene.h"

#include "Graphics/modelObject.h"   // 3d abstract
#include "Graphics/viewObject.h"    // 2d abstract

#include "Camera.h"


Camera * Camera::mpInstance = NULL;

Camera::Camera ()
:  Body (1280, 720)
{
   sf::WindowSettings Settings;
   Settings.DepthBits         = 24; // Request a 24 bits depth buffer
   Settings.StencilBits       = 8;  // Request a 8 bits stencil buffer
   Settings.AntialiasingLevel = 2;  // Request 2 levels of antialiasing
   mpWindow = new sf::RenderWindow ();
   mpWindow->Create (sf::VideoMode (800, 600, 32), "Highrise Developer (version " HR_VERSION ")", sf::Style::Close|sf::Style::Resize, Settings);
   mZoomFactor = -400; // back away 200 feet
   mAspect = (float)(800.0 / 600);
   mCam.x = 800;
   mCam.y = 600;
   mIgnoreCamera = false;
   mpInput = &(mpWindow->GetInput ());
   ms.x = -620;
   ms.y = -170;
   mpWindow->ShowMouseCursor (false);
}

const sf::Input *
Camera::GetInput ()
{
   return mpInput;
}

Vector2i
Camera::GetMouse ()
{
   Vector2f ms2( ms.x, ms.y );
   return ms2 + GetLocalMouse();
}

Vector2i
Camera::GetLocalMouse()
{
   return Vector2i (mpInput->GetMouseX (), mpInput->GetMouseY ());
}


void
Camera::SetMaxFramerate (int rate)
{
   mpWindow->SetFramerateLimit (rate);
}

void
Camera::SetSceneSize (Vector2f Size)
{
   glClearDepth(1.0f);
   mScene.x = Size.x;
   mScene.y = Size.y;
}

Camera*
Camera::GetInstance()
{
   if (mpInstance == NULL)
   {
      mpInstance = new Camera ();
   }
   return mpInstance;
}

void

// modes functions
Camera::Clear ()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
Camera::SetActive()
{
   glViewport(0, 0, (GLsizei)mCam.x, (GLsizei)mCam.y);//this->ms.x, ms.y); these were negative need to fixe this so the
   glEnable(GL_TEXTURE_2D);
//   mpWindow->SetActive (true);
}

void
Camera::Display ()
{
   mpWindow->Display ();
}

void
Camera::Center (int x, int y)
{
   ms.x = -550; //x - (mViewRect.Left / 2);
   ms.y = -200; //y - (mViewRect.Top / 2);
}

bool
Camera::OnResize (Vector2i vi)
{
   glViewport(0, 0, vi.x, vi.y);
   mCam = vi;
   mAspect = (float)(vi.x) / vi.y;
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
	gluPerspective (90.0f,mAspect ,1.0f,1000.0f);		// Calculate The Aspect Ratio Of The Window
   return true;
}

void
Camera::InitGL()
{
	glShadeModel(GL_SMOOTH);												// Enable Smooth Shading
	glClearDepth(1.0f);														// Depth Buffer Setup
   glClearColor(0.f, 0.f, 0.f, 0.f);
	glDepthFunc(GL_LEQUAL);													// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);						// Really Nice Perspective Calculations
   glEnable (GL_TEXTURE_2D);

   // Enable Z-buffer read and write
   glEnable(GL_DEPTH_TEST);
   glDepthMask(GL_TRUE);

   // Setup a perspective projection
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(90.0f, mAspect, 1.0f, 1000.f);
   glEnable (GL_TEXTURE_2D);
}

void
Camera::DrawModel (Scene* pModel)   // 3d interface objects
{
//   glDisable (GL_LIGHTING);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   {                       // brackets just keep the code in push and pop uniform
      glEnable (GL_TEXTURE_2D);
      glTranslatef (GetPositionX(), GetPositionY(), mZoomFactor);
      glColor4ub (255,255,255,255);
      glEnable(GL_BLEND);
      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA  );

      pModel->Draw();
      glDisable(GL_BLEND);
   }
   glPopMatrix();
}

void
Camera::DrawInterface(Interface* pI)   // 2d interface objects
{
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
      glLoadIdentity();
      glEnable (GL_TEXTURE_2D);
      glTranslatef ( (GLfloat)(-0.3125*mWidth.x), (GLfloat)(mHeight.y/2-144), -380);
//      glTranslatef (GetPositionX(), GetPositionY(), mZoomFactor);
      glColor4ub (255,255,255,255);
      glEnable(GL_BLEND);
      glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA  );
      pI->Draw();
      glDisable(GL_BLEND);
   glPopMatrix();
}

#define BUFFER_LENGTH 64   // max click hits we expect but we might get 2

int Camera::RenderFramework(Scene* pModel, Vector2f mouse)
{
   int iResult = 0;

   glPushAttrib(GL_ALL_ATTRIB_BITS);

   glDisable (GL_LIGHTING);
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
   glInitNames();
   glPushName(0);

   gluPickMatrix(mouse.x, mouse.y, 2, 2, viewport);
   
   // Apply perspective matrix 
   gluPerspective(90.0f, mAspect, 1.0f, 1000.f);		// Calculate The Aspect Ratio Of The Window
   glTranslatef (GetPositionX(), GetPositionY(), mZoomFactor);
   
   // Draw the scene
   pModel->RenderFramework();
   
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
         iResult = selectBuff[3]; // ok what did we hit
      }
   }
   glPopAttrib();
   return iResult; // the object id
}

bool
Camera::GetEvent (sf::Event & event)
{
   return mpWindow->GetEvent (event);
}

bool
Camera::OnKeyDown (sf::Key::Code Key)
{
   if (Key == sf::Key::D)
   {
      mv.x = -200;
      ma.x = 150;
   }
   if (Key == sf::Key::S)
   {
      mv.y = 200;
      ma.y = -150;
   }
   if (Key == sf::Key::A)
   {
      mv.x = 200;
      ma.x = -150;
   }
   if (Key == sf::Key::W)
   {
      mv.y = -200;
      ma.y = 150;
   }
   if (Key == sf::Key::E)
   {
      SetVelocity (0, 0);
   }
   return true;
}

bool
Camera::OnMouseWheel (int Delta)
{
   if (Delta > 0)
      ZoomIn();
   else
      ZoomOut();
   return true;
}

void
Camera::ZoomIn()
{
   Zoom(10);
}
void
Camera::ZoomOut()
{
   Zoom(-10);
}

void
Camera::Zoom(float Factor)
{
   //Rectf ZoomedRect;
   // Calcuate the center
   if( Factor < 0 && mZoomFactor > -900 || Factor > 0 && mZoomFactor < -40 )
   {
      mZoomFactor += Factor;
   }
   std::cout << "ZF=" << mZoomFactor << "\n";
}
