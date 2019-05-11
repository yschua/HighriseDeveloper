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

#include "Interface.h"

#include "../Graphics/Animation.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Image.h"
#include "../Root/Physics.h"
#include "../Settings/Settings.h"
#include "../Types/String.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string.h>

using namespace Gfx;

Interface::Interface()
{
    mLanguageCode = 0;
    mSoundFxOn = false;
    mMusicOn = false;
    LoadSettings();
    mChangedSettings = false;
    mCurDay = 0;
    m_ticks = 0;

    UpdateStats();
}

Interface::~Interface()
{
    if (mChangedSettings) {
        SaveSettings();
    }
}

void Interface::LoadSettings()
{
    Settings::SettingsIni theSettings;
    theSettings.Load();
    bool bHasSettings = false;
    if (theSettings.SettingsAreLoaded()) {
        int iCode = FromString<int>(theSettings.Get("Language.Code"));
        if (iCode > 0 && iCode < 5) {
            SetLanguageCode(iCode);
            bHasSettings = true;
        }
        mSoundFxOn = (theSettings.Get("Sound.FX")[0] == '1'
                          ? true
                          : false); // its a string, at the least it will have a null terminator
        mMusicOn = (theSettings.Get("Sound.Music")[0] == '1' ? true : false);
    }
    if (!bHasSettings) {
        SetLanguageCode(1);
        theSettings.Set("Sound.FX", (mSoundFxOn) ? "1" : "0", false);
        theSettings.Set("Sound.Music", (mMusicOn) ? "1" : "0", false);
        theSettings.Set("Language.Code", "1", true);
    }
}

void Interface::SaveSettings()
{
    Settings::SettingsIni theSettings;
    theSettings.Load();
    bool bHasSettings = false;
    // char buf[8];
    if (theSettings.SettingsAreLoaded()) {

        theSettings.Set("Sound.FX", (mSoundFxOn) ? "1" : "0", false);
        theSettings.Set("Sound.Music", (mMusicOn) ? "1" : "0", false);
        theSettings.Set("Language.Code", ToString(mLanguageCode), true);
    }
}

void Interface::SetLanguageCode(int code)
{
    mLanguageCode = code;
    mClock.SetLanguage(code);
    mChangedSettings = true;
    mCurDay = 0;
}

void Interface::SetSoundFx(bool bFX)
{
    mSoundFxOn = bFX;
    // toddle the sound fx
    mChangedSettings = true;
    mCurDay = 0;
}

void Interface::SetMusic(bool bMusic)
{
    mMusicOn = bMusic;
    // toggle the music player
    mChangedSettings = true;
    mCurDay = 0;
}

bool Interface::UpdateTime(int clockRate)
{
    if (m_ticks++ < clockRate) return false;

    m_ticks = 0;
    mClock.Update(1);
	return true;
}

void Interface::Draw()
{
    mClock.Draw();
    mStats.Draw();
}

void Interface::UpdateStats()
{
    if (mClock.GetDayOfYear() != mCurDay) {
        mStats.SetDayOfWeek(mClock.DayOfWeekToString());
        mStats.SetDate(mClock.DateString());
        mCurDay = mClock.GetDayOfYear();
    }
    mStats.Update();
}
