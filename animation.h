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
#include "physics.h"
#include "Graphics/texture.h"

using namespace Gfx;

class Animation : public Body
{
private:
//   std::vector <std::pair <sf::Image *, float> > mframes;
   std::vector <std::pair <Texture*, float> > mframes;
   int mcurrent_frame;
   float mtime;
//   sf::Sprite * sprite;

public:
   Animation (int width, int height);
//   void AddFrame (sf::Image * image, float duration);
   void AddFrame (Texture* pTex, float duration);
   void Update (float dt);
   unsigned int GetTextureID();
};

class AnimationSingle : public Body
{
   Texture* mpTexture;
public:
   //sf::Sprite* mSprite;
   //AnimationSingle (sf::Image* image);
   AnimationSingle (Texture* pTex, int width, int height);
   void SetSubRect (int x1, int y1, int x2, int y2);
   unsigned int GetTextureID();

};

#endif
