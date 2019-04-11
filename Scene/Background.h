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

#ifndef _BACKGROUND_H
#define _BACKGROUND_H

#include "../Graphics/ModelObject.h"
class AnimationSingle;
class Tiler;

enum BackLight_State {
    BLS_Night = 0, // just dark
    BLS_Dawn,      // incresing light to dawn
    BLS_Day,       // incresing light to daylight
    BLS_Dusk,      // fading light to red glow dusk
    BLS_Twilight,  // intermediate fade to twilight
    BLS_Reset      // set back to night and go dark
};

class Background : public Gfx::ModelObject
{
private:
    AnimationSingle* mBackImage;
    Tiler* mBackBuildings;
    Tiler* mBackGround;
    BackLight_State mLightState;
    float mRGBALight[4];
    float mRGBATransition[4];
    int mStepsToTransition; // countdown to zero
    int mNextTimeEvent;

public:
    void Update(int TimeOfDay);
    void Draw();
    Background(float left, float top, float width, float height);
    int RenderFramework(int id) { return id; }; // don't click this, yet
};

#endif //_BACKGROUND_H
