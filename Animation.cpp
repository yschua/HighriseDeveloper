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

#include <vector>
//#include <SFML/System.hpp>
//#include <SFML/Graphics.hpp>

#include "Physics.h"
#include "Animation.h"

Animation::Animation (int width, int height)
:  AnimationBase (width, height)
{
   mCurrentFrame = 0;
   mTime = 0;
//   sprite = new sf::Sprite ();
}

void
Animation::AddFrame (Texture* pTex, float duration)
{
   mFrames.push_back (std::pair<Texture*, float> (pTex, duration));
}

void
Animation::BindTexture()
{
   return mFrames[mCurrentFrame].first->Bind();
}

void
Animation::Update (float dt)
{
   mTime += dt;
   if (mTime > mFrames[mCurrentFrame].second)
   {
      mTime = 0;
      mCurrentFrame++;
      if (mCurrentFrame >= mFrames.size ())
         mCurrentFrame = 0;
//      sprite->SetImage (*mframes[mcurrent_frame].first);
   }
}

AnimationSingle::AnimationSingle (Texture* pTex, int width, int height)
:  AnimationBase( width, height )
{
   mpTexture = pTex;
//   mSprite = new sf::Sprite ();
//   mSprite->SetImage (*image);
}

void
AnimationSingle::SetSubRect (int x1, int y1, int x2, int y2)
{
//   sf::IntRect* subrect = new sf::IntRect (x1, y1, x2, y2);
//   mSprite->SetSubRect (*subrect);
}

void
AnimationSingle::BindTexture()
{
   return mpTexture->Bind();
   //return 2;
}

AnimationEmpty::AnimationEmpty ( int width, int height)
:  AnimationBase (width, height)
{
}

