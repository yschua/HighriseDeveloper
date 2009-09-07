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

#include "physics.h"
#include "camera.h"
#include "event.h"

EventHandler::EventHandler ()
{
   Cam = Camera::GetInstance ();
   mpInput = Cam->GetInput ();
}

void
EventHandler::Add (EventBase * Handler)
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
         for (std::list <EventBase *>::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->KeyDown (Event.Key.Code))
               break; // break if one of our handlers returned true; ie the event was eaten
      }
      else if (Event.Type == sf::Event::Resized)
      {
         for (std::list <EventBase *>::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->Resize (Event.Size.Width, Event.Size.Height))
               break;
      }
      else if (Event.Type == sf::Event::KeyReleased)
      {
         for (std::list <EventBase *>::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->KeyUp (Event.Key.Code))
               break;
      }
      else if (Event.Type == sf::Event::MouseButtonPressed)
      {
         for (std::list <EventBase *>::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->MouseDown (Event.MouseButton.Button, mpInput->GetMouseX (), mpInput->GetMouseY (), mpInput->GetMouseX (), mpInput->GetMouseY ()))
               break;
      }
      else if (Event.Type == sf::Event::MouseButtonReleased)
      {
         for (std::list <EventBase *>::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->MouseUp (Event.MouseButton.Button, mpInput->GetMouseX (), mpInput->GetMouseY (), mpInput->GetMouseX (), mpInput->GetMouseY ()))
               break;
      }
      else if (Event.Type == sf::Event::MouseMoved)
      {
         for (std::list <EventBase *>::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->MouseMove (mpInput->GetMouseX (), mpInput->GetMouseY (), mpInput->GetMouseX (), mpInput->GetMouseY ()))
               break;
      }
   }
   return true;
}
