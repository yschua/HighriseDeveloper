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
#include <list>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Types/Vector2.h"
#include "../camera.h"
#include "event.h"

EventHandler::EventHandler ()
{
   Cam = Camera::GetInstance ();
   mpInput = Cam->GetInput ();
}

void
EventHandler::Add (EventBase* Handler)
{
   mHandlers.push_back (Handler);
}

bool
EventHandler::HandleEvents ()
{
   sf::Event Event;
   while (Cam->GetEvent (Event))
   {
      if (Event.Type == sf::Event::KeyPressed)
      {
         for (ConType::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->KeyDown (Event.Key.Code))
               return true;
               //break; // break if one of our handlers returned true; ie the event was eaten
      }
      else if (Event.Type == sf::Event::Resized)
      {
         for (ConType::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->Resize (Vector2i(Event.Size.Width, Event.Size.Height)))
               return true;
      }
      else if (Event.Type == sf::Event::KeyReleased)
      {
         for (ConType::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->KeyUp (Event.Key.Code))
               return true;
      }
      else if (Event.Type == sf::Event::MouseButtonPressed)
      {
         for (ConType::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->MouseDown (Event.MouseButton.Button, Vector2i(mpInput->GetMouseX (), mpInput->GetMouseY ()), Vector2i(mpInput->GetMouseX (), mpInput->GetMouseY ())))
               return true;
      }
      else if (Event.Type == sf::Event::MouseButtonReleased)
      {
         for (ConType::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->MouseUp (Event.MouseButton.Button, Vector2i(mpInput->GetMouseX (), mpInput->GetMouseY ()), Vector2i(mpInput->GetMouseX (), mpInput->GetMouseY ())))
               return true;
      }
      else if (Event.Type == sf::Event::MouseMoved)
      {
         for (ConType::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->MouseMove (Vector2i(mpInput->GetMouseX (), mpInput->GetMouseY ()), Vector2i(mpInput->GetMouseX (), mpInput->GetMouseY ())))
               return true;
      }
   }
   return false;
}
