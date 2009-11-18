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
#include <SFML/Graphics.hpp>
#include <string.h>
#include <map>
#include "../Types/String.h"
#include "../Settings/Settings.h"
#include "../Root/Physics.h"
#include "../Graphics/Image.h"
#include "../Graphics/Animation.h"
#include "../Graphics/Camera.h"
#include "Interface.h"

using namespace Gfx;

Interface::Interface ()
{
   mLanguageCode = 0;
   LoadSettings();
   mChangedSettings = false;
}

Interface::~Interface ()
{
   if (mChangedSettings)
   {
      SaveSettings();
   }
}

void Interface::LoadSettings()
{
   Settings::SettingsIni theSettings;
   theSettings.Load();
   bool bHasSettings = false;
   if( theSettings.SettingsAreLoaded() )
   {
      int iCode = FromString<int>(theSettings.Get("Language.Code"));
      if( iCode >0 && iCode < 5 )
      {
         SetLanguageCode (iCode);
         bHasSettings = true;
      }
   }
   if (!bHasSettings)
   {
      SetLanguageCode (1);
      theSettings.Set ("Language.Code", "1", true);
   }
}

void Interface::SaveSettings()
{
   Settings::SettingsIni theSettings;
   theSettings.Load();
   bool bHasSettings = false;
   char buf[8];
   if( theSettings.SettingsAreLoaded() )
   {
      _itoa_s(mLanguageCode, buf ,8 , 10);
      theSettings.Set ("Language.Code", buf, true);
   }
}

void Interface::SetLanguageCode (int code)
{
   mLanguageCode = code;
   mClock.SetLanguage (code);
   mChangedSettings = true;
}

void Interface::PosCalc ()
{
}

void Interface::Update (float dt)
{
   static float count = 0;
   mClock.Update(1); // 1 minute update
   if( ++count > dt )
   {
      count = 0;
      mStats.SetDayOfWeek (mClock.DayOfWeekToString());
      mStats.Update();
   }
}

void Interface::Draw ()
{
   mClock.Draw ();
   mStats.Draw ();
}
