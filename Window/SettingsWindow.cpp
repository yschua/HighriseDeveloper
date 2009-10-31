 /***********************************************************************
 filename:   Theme Park application
 *   Thanks to Paul D Turner & The CEGUI Development Team for samples
 *
 *   This file is part of Extreme Park Developer.
 *
 *   Extreme Park Developer is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Extreme Park Developer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Extreme Park Developer.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <CEGUI.h>
#include "SettingsWindow.h"
#define LOOK "WindowsLook"

SettingsWindow::SettingsWindow()
{
   mpWnd = NULL;
}

SettingsWindow::~SettingsWindow()
{
   if (mpWnd != NULL)
   {
      Destroy();
   }
}

/*************************************************************************
Sample specific initialisation goes here.
*************************************************************************/
bool SettingsWindow::Create (CEGUI::Window* pRoot)
{
   using namespace CEGUI;

// Code provided by Paul D Turner (C) 2005
   CEGUI::WindowManager& winMgr = CEGUI::WindowManager::getSingleton();
   // A FrameWindow is a window with a frame and a titlebar which may be moved around
   // and resized.
   //
   // Create a FrameWindow in the TaharezLook style, and name it 'Demo Window'
   mpWnd = (FrameWindow*)winMgr.createWindow( LOOK "/FrameWindow", "Settings");
   // Here we attach the newly created FrameWindow to the previously created
   // DefaultWindow which we will be using as the root of the displayed gui.
   pRoot->addChildWindow(mpWnd);

   // Windows are in Relative metrics mode by default.  This means that we can
   // specify sizes and positions without having to know the exact pixel size
   // of the elements in advance.  The relative metrics mode co-ordinates are
   // relative to the parent of the window where the co-ordinates are being set.
   // This means that if 0.5f is specified as the width for a window, that window
   // will be half as its parent window.
   //
   // Here we set the FrameWindow so that it is half the size of the display,
   // and centered within the display.
   mpWnd->setPosition(UVector2(cegui_reldim(0.25f), cegui_reldim( 0.25f)));
   mpWnd->setSize(UVector2(cegui_reldim(0.5f), cegui_reldim( 0.5f)));

   // now we set the maximum and minum sizes for the new window.  These are
   // specified using relative co-ordinates, but the important thing to note
   // is that these settings are aways relative to the display rather than the
   // parent window.
   //
   // here we set a maximum size for the FrameWindow which is equal to the size
   // of the display, and a minimum size of one tenth of the display.
   mpWnd->setMaxSize(UVector2(cegui_reldim(1.0f), cegui_reldim( 1.0f)));
   mpWnd->setMinSize(UVector2(cegui_reldim(0.1f), cegui_reldim( 0.1f)));
   mpWnd->setText("Highrise Developer Preferences");


   // Code by AlabamaCajun
   Window* pLabel1 = winMgr.createWindow( LOOK "/StaticText", "Highrise/ControlPanel/Label1");
   Window* pLabel2 = winMgr.createWindow( LOOK "/StaticText", "Highrise/ControlPanel/Label2");
   // Sound Label
   pLabel1->setProperty("FrameEnabled", "false");
   pLabel1->setProperty("BackgroundEnabled", "false");
   pLabel1->setPosition(UVector2(cegui_reldim(0.02f), cegui_reldim( 0.1f)));
   pLabel1->setSize(UVector2(cegui_reldim(0.26f), cegui_reldim( 0.1f)));
   pLabel1->setText("Enable Sound:");
   // Sound Enable CheckBox
   CEGUI::Checkbox* pBox1 = static_cast<CEGUI::Checkbox*>(winMgr.createWindow(LOOK "/Checkbox", "Settings/SoundChechBox"));
   pBox1->setSize(UVector2(cegui_reldim(0.1f), cegui_reldim( 0.1f)));
   pBox1->setPosition(UVector2(cegui_reldim(0.32f), cegui_reldim( 0.1f)));

   // Music Label
   pLabel2->setProperty("FrameEnabled", "false");
   pLabel2->setProperty("BackgroundEnabled", "false");
   pLabel2->setPosition(UVector2(cegui_reldim(0.02f), cegui_reldim( 0.2f)));
   pLabel2->setSize(UVector2(cegui_reldim(0.2f), cegui_reldim( 0.1f)));
   pLabel2->setText("Enable Music:");
   // Music Enable CheckBox
   CEGUI::Checkbox* pBox2 = static_cast<CEGUI::Checkbox*>(winMgr.createWindow(LOOK "/Checkbox", "Settings/MusicChechBox"));
   pBox2->setSize(UVector2(cegui_reldim(0.1f), cegui_reldim( 0.1f)));
   pBox2->setPosition(UVector2(cegui_reldim(0.32f), cegui_reldim( 0.2f)));

   mpWnd->addChildWindow(pLabel1);
   mpWnd->addChildWindow(pLabel2);

   mpWnd->addChildWindow(pBox1);
   mpWnd->addChildWindow(pBox2);

   mpWnd->subscribeEvent (FrameWindow::EventCloseClicked, Event::Subscriber(&SettingsWindow::OnSoundCheck, this));
   mpWnd->subscribeEvent (FrameWindow::EventCloseClicked, Event::Subscriber(&SettingsWindow::OnMusicCheck, this));

   // subscribe handler that closes the dialog
   mpWnd->subscribeEvent (FrameWindow::EventCloseClicked, Event::Subscriber(&SettingsWindow::OnClose, this));
   return true;
}

bool SettingsWindow::OnClose(const CEGUI::EventArgs& e)
{
   Destroy();
   return true;
}

bool SettingsWindow::OnSoundCheck(const CEGUI::EventArgs& e)
{
   return true;
}

bool SettingsWindow::OnMusicCheck(const CEGUI::EventArgs& e)
{
   return true;
}

/*************************************************************************
Cleans up resources allocated in the initialiseSample call.
*************************************************************************/
void SettingsWindow::Destroy()
{
   using namespace CEGUI;
   if (mpWnd != NULL)
   {
      CEGUI::WindowManager& winMgr = CEGUI::WindowManager::getSingleton();
      winMgr.destroyWindow(mpWnd);
      mpWnd = NULL;
   }
}
