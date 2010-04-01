/*   This file is part Highrise Developer.
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

#pragma once
#ifndef _SETTINGSWINDOW_H
#define _SETTINGSWINDOW_H

class Interface;

namespace CEGUI
{
   class FrameWindow;
}

class SettingsWindow
{
protected:
   CEGUI::FrameWindow* mpWnd;
   CEGUI::Checkbox* mpSoundFx;
   CEGUI::Checkbox* mpMusic;
   Interface& mInterface;
public:
   SettingsWindow (Interface& rInterface);
   ~SettingsWindow ();

public:
   bool Create(CEGUI::Window* pRoot);
   void Destroy ();

   bool OnMusicCheck(const CEGUI::EventArgs& e);
   bool OnSoundCheck(const CEGUI::EventArgs& e);
   bool OnClose (const CEGUI::EventArgs& e);
   bool OnEnglish(const CEGUI::EventArgs& e);
   bool OnSpanish(const CEGUI::EventArgs& e);
   bool OnFrench(const CEGUI::EventArgs& e);
   bool OnDeutsch(const CEGUI::EventArgs& e);
   bool OnItalian (const CEGUI::EventArgs& e);
};

#endif // _SETTINGSWINDOW_H
