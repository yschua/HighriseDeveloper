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
#ifdef WIN32
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "physics.h"
#include "animation.h"
#else
#include "highrisedev.h"
#endif

Animation::Animation (int width, int height)
:  Body (width, height)
{
   mcurrent_frame = 0;
   mtime = 0;
//   sprite = new sf::Sprite ();
}

void
Animation::AddFrame (Texture* pTex, float duration)
{
   mframes.push_back (std::pair<Texture*, float> (pTex, duration));
}

unsigned int 
Animation::GetTextureID()
{
   return mframes[mcurrent_frame].first->GetID();
}

void
Animation::Update (float dt)
{
   mtime += dt;
   if (mtime > mframes[mcurrent_frame].second)
   {
      mtime = 0;
      mcurrent_frame++;
      if (mcurrent_frame >= mframes.size ())
         mcurrent_frame = 0;
//      sprite->SetImage (*mframes[mcurrent_frame].first);
   }
}

AnimationSingle::AnimationSingle (Texture* pTex, int width, int height)
:  Body( width, height )
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

unsigned int 
AnimationSingle::GetTextureID()
{
   return mpTexture->GetID();
   //return 2;
}
