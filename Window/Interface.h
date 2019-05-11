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

#pragma once
#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "Clock.h"
#include "Stats.h"

class Interface
{
private:
    bool mChangedSettings;
    bool mSoundFxOn;
    bool mMusicOn;
    int mLanguageCode;
    int mCurDay;
    int m_ticks;

public: // these should be protected
    Clock mClock;
    Stats mStats;

public:
    Interface();
    ~Interface();

    void SetLanguageCode(int code);
    void SetSoundFx(bool bFX);
    void SetMusic(bool bMusic);
    int GetLanguageCode() { return mLanguageCode; }
    bool GetSoundFx() { return mSoundFxOn; }
    bool GetMusic() { return mMusicOn; }

    void LoadSettings();
    void SaveSettings();

    int GetTimeOfDay() { return mClock.GetTimeOfDay(); }
    int GetDayOfYear() { return mClock.GetDayOfYear(); }

    bool UpdateTime(int clockRate);
    void UpdateStats();
    void Draw();
};

#endif // _INTERFACE_H
