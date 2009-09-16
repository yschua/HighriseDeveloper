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

#include <vector> // changed from list to vector so the collection can be scrolled in up and down
#include <list>

#include "../animation.h"
//#include "tiler.h"
#include "../image.h"
#include "../routes.h"
#include "../physics.h"
#include "elevatorBase.h"
#include "elevator.h"
#include "floorBase.h"
#include "level.h"
#include "lobby.h"
#include "apartment.h"
#include "office.h"
#include "damage.h"
#include "tower.h"

#include "../highriseException.h"
// This is a debug stub to load a building for early dev

void
Tower::DebugLoad (int x, int y, int x2)
{
   try
   {
      Elevator* pElevator = new Elevator( Elevator::LS_Standard, 472, -1, 6, this );
      GetRoutes().AddRoute( pElevator );
      pElevator = new Elevator( Elevator::LS_Standard, 472 + 36 + 9, 0, 5, this );
      GetRoutes().AddRoute( pElevator );
      // stuffing the floors with test spaces
      office* my_office = new office(400, 1, this);
      office* my_office2 = new office (400, 2, this);
      office* my_office3 = new office (472, 1, this);
      office* my_office4 = new office (472, 2, this);
      office* my_office5 = new office (544, 1, this);
      office* my_office6 = new office (544, 2, this);
      office* my_office7 = new office (400, 3, this);
      office* my_office8 = new office (472, 3, this);
      office* my_office9 = new office (544, 3, this);

      Apartment* my_apt1 = new Apartment (400, 4, this);
      Apartment* my_apt2 = new Apartment (472, 4, this);
      Apartment* my_apt3 = new Apartment (544, 4, this);
      Apartment* my_apt4 = new Apartment (472, 5, this);
      Apartment* my_apt5 = new Apartment (544, 5, this);

      office* my_basement = new office (400, -1, this);

      Level* sublevel = GetLevel(-1);
      sublevel->SetFloorPositions(400, 544+72);
      Level* level_1 = NewLevel (400, 1, 544+72);
      Level* level_2 = NewLevel (400, 2, 544+72);
      Level* level_3 = NewLevel (400, 3, 544+72);
      Level* level_4 = NewLevel (400, 4, 544+72);
      Level* level_5 = NewLevel (400, 5, 544+72);
      Level* level_6 = NewLevel (400, 6, 544+72);
      level_1->AddFloor (my_office);
      level_1->AddFloor (my_office3);
      level_1->AddFloor (my_office5);
      level_2->AddFloor (my_office2);
      level_2->AddFloor (my_office4);
      level_2->AddFloor (my_office6);
      level_3->AddFloor (my_office7);
      level_3->AddFloor (my_office8);
      level_3->AddFloor (my_office9);
      level_4->AddFloor (my_apt1);
      level_4->AddFloor (my_apt2);
      level_4->AddFloor (my_apt3);
      level_5->AddFloor (my_apt4);
      level_5->AddFloor (my_apt5);
      sublevel->AddFloor (my_basement);

      // Test Add floorspace
      bool bAvail = level_6->IsSpaceEmpty(400, 472);
      if (bAvail)
      {
         Apartment* new_apt = new Apartment (400, 6, this);
         level_6->AddFloor (new_apt);
      }
      // Test Add floorspace
      bAvail = level_5->IsSpaceEmpty(400, 472);
      if (bAvail)
      {
         ImageManager * image_man = ImageManager::GetInstance ();
         Damage* new_dmg = new Damage (400, 472, 5, this, new AnimationSingle (image_man->GetTexture ("office_damage.png", GL_RGBA), 72, 36 ));
         level_5->AddFloor (new_dmg);
      }
   }
   catch (...)
   {
      throw new HighriseException ("Debug Alpha Building failed to create");
   }
}

