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

#include "highrisedev.h"

using namespace Gfx;

office_state
office::unoccupied_day (float dt)
{
   if (rand () % 50 == 3)
      return s_occupied_day;
   return s_unoccupied_day;
}

office_state
office::occupied_day (float dt)
{
   if (rand () % 50 == 3)
      return s_unoccupied_day;
   return s_occupied_day;
}

office::office (int x, int level, Tower * TowerParent)
      :  mcurrent_state (s_unoccupied_day)
      ,  FloorBase (x, x + 72, level, TowerParent)
{
   ImageManager * image_man = ImageManager::GetInstance ();
   std::cout << "New office at " << mx << ", " << my << " level " << mlevel << std::endl;
   manimations[s_occupied_day] = new Animation ();
   manimations[s_occupied_day]->AddFrame (image_man->GetImg ("office_o_d_1.png"), 1000);
   manimations[s_occupied_day]->AddFrame (image_man->GetImg ("office_o_d_2.png"), 1000);
   manimations[s_occupied_day]->AddFrame (image_man->GetImg ("office_o_d_3.png"), 1000);
   manimations[s_occupied_day]->AddFrame (image_man->GetImg ("office_o_d_4.png"), 1000);
   manimations[s_occupied_day]->AddFrame (image_man->GetImg ("office_o_d_5.png"), 1000);
   manimations[s_occupied_day]->SetPosition (mx, my);
   manimations[s_unoccupied_day] = new Animation ();
   manimations[s_unoccupied_day]->AddFrame (image_man->GetImg ("office_u_d.png"), 1000);
   manimations[s_unoccupied_day]->SetPosition (mx, my);
}

void
office::Update (float dt)
{
   manimations[mcurrent_state]->Update (dt);
   office_state new_state;
   switch (mcurrent_state)
   {
      case s_unoccupied_day :
         new_state = unoccupied_day (dt);
         break;
      case s_occupied_day :
         new_state = occupied_day (dt);
         break;
   }
   mcurrent_state = new_state;
}

void
office::Draw ()
{
   Camera::GetInstance()->Draw (*manimations[mcurrent_state]);
}
