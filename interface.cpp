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

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>
#include <map>
#include "physics.h"
#include "image.h"
#include "animation.h"
#include "Camera.h"
#include "interface.h"

using namespace Gfx;

Interface::Interface ()
{
}

void
Interface::PosCalc ()
{
}

void
Interface::Update (float dt)
{
   mClock.Update(1); // 1 minute update
}

void
Interface::Draw ()
{
   mClock.Draw ();
}
