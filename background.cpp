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
#include <iostream>
#include <map>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "physics.h"
#include "image.h"
#include "camera.h"
#include "animation.h"
#include "tiler.h"
#include "floorBase.h"

#include "background.h"
#else
#include "highrisedev.h"
#endif

C_Background::C_Background ()
{
   C_ImageManager * images = C_ImageManager::GetInstance ();
   cam = C_Camera::i();
   m_BackImage = new C_AnimationSingle (images->GetImg ("back.png"));
   // move the ground down 36 since lobby is at 0
   m_BackBuildings = new C_Tiler (images->GetImg ("buildings.png"), C_Tiler::Horizontal, 0, cam->GetWorldX (), cam->GetWorldY () + 36 - 64);
   m_BackGround = new C_Tiler (images->GetImg ("ground.png"), C_Tiler::Horizontal, 0, cam->GetWorldX (), cam->GetWorldY () + 36);
}

void
C_Background::Draw ()
{
   cam->Draw (*m_BackImage);
   cam->Draw (*m_BackBuildings);
   cam->Draw (*m_BackGround);
}
