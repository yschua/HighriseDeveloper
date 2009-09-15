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
// Tick Tock!

#pragma once
#ifndef _CLOCK_H
#define _CLOCK_H

#include "Graphics/viewObject.h"
#include "animation.h"

class AnimationSingle;

class Clock : public Gfx::ViewObject
{
   AnimationSingle * mClockFace;
   int mTimeOfDay;
   int mDayOfYear;
   int mYear;

   // These will pump directly into the transform for the hands
   float mAngleHour;  // for the render
   float mAngleMinute;

   SimpleQuad mMinuteHand;
   SimpleQuad mHourHand;
public:
   Clock ();
   ~Clock ();
   void PosCalc ();
   void Update (int minutes);
   void Draw ();

};

#endif // _CLOCK_H
