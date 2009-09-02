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

Animation::Animation ()
{
   mcurrent_frame = 0;
   mtime = 0;
   sprite = new sf::Sprite ();
}

void
Animation::AddFrame (sf::Image * image, float duration)
{
   mframes.push_back (std::pair<sf::Image *, float> (image, duration));
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
      sprite->SetImage (*mframes[mcurrent_frame].first);
   }
}

AnimationSingle::AnimationSingle (sf::Image* image)
{
   mSprite = new sf::Sprite ();
   mSprite->SetImage (*image);
}

void
AnimationSingle::SetSubRect (int x1, int y1, int x2, int y2)
{
   sf::IntRect* subrect = new sf::IntRect (x1, y1, x2, y2);
   mSprite->SetSubRect (*subrect);
}
