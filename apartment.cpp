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
#include "camera.h"
#include "image.h"
#include "animation.h"
#include "floorBase.h"

#include "apartment.h"
#else
#include "highrisedev.h"
#endif

//   apt_unoccupied_day,
//   apt_occupied_day,
//   apt_occupied_night,
//   apt_sleep_night

apartment_state
C_Apartment::unoccupied_day (float dt)
{
   if (rand () % 50 == 3)
      return apt_occupied_day;
   return apt_unoccupied_day;
}

apartment_state
C_Apartment::occupied_day (float dt)
{
   if (rand () % 50 == 3)
      return apt_unoccupied_day;
   return apt_occupied_day;
}

apartment_state
C_Apartment::occupied_night (float dt)
{
   return apt_occupied_sleep;
}

apartment_state
C_Apartment::occupied_sleep (float dt)
{
   return apt_occupied_day;
}

C_Apartment::C_Apartment (int x, int level, C_Tower * TowerParent)
      :  m_current_state (apt_occupied_day)
      ,  C_FloorBase (x, x + 72, level, TowerParent)
{
   C_ImageManager * image_man = C_ImageManager::GetInstance ();
   std::cout << "New apartment at " << m_x << ", " << m_y << " level " << m_level << std::endl;
   m_animations[apt_occupied_day] = new C_Animation ();
   m_animations[apt_occupied_day]->AddFrame (image_man->GetImg ("apartment_r_d_1.png"), 1000);
   m_animations[apt_occupied_day]->AddFrame (image_man->GetImg ("apartment_r_n_1.png"), 1000);
   m_animations[apt_occupied_day]->SetPosition (m_x, m_y);
   m_animations[apt_unoccupied_day] = new C_Animation ();
   m_animations[apt_unoccupied_day]->AddFrame (image_man->GetImg ("apartment_r_s_1.png"), 1000);
   m_animations[apt_unoccupied_day]->SetPosition (m_x, m_y);
}

void
C_Apartment::Update (float dt)
{
   m_animations[m_current_state]->Update (dt);
   apartment_state new_state;
   switch (m_current_state)
   {
      case apt_unoccupied_day :
         new_state = unoccupied_day (dt);
         break;
      case apt_occupied_day :
         new_state = occupied_day (dt);
         break;
   }
   m_current_state = new_state;
}

void
C_Apartment::Draw ()
{
   C_Camera::i()->Draw (*m_animations[m_current_state]);
}
