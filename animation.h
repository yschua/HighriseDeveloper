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

#ifndef _ANIMATION_H
#define _ANIMATION_H

class Animation : public Body
{
private:
   std::vector <std::pair <sf::Image *, float> > mframes;
   int mcurrent_frame;
   float mtime;

public:
   Animation ();
   void AddFrame (sf::Image * image, float duration);
   void Update (float dt);
   sf::Sprite * sprite;
};

class AnimationSingle : public Body
{
public:
   sf::Sprite * sprite;
   AnimationSingle (sf::Image * image);
   void SetSubRect (int x1, int y1, int x2, int y2);
};

#endif
