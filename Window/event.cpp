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
#include "../Camera.h"
#include "event.h"

EventHandler::EventHandler ()
{
   Cam = Camera::GetInstance ();
   mpInput = Cam->GetInput();
}

void
EventHandler::Add (EventBase* Handler)
{
   mHandlers.push_back (Handler);
}

bool EventHandler::HandleEvents (const sf::Event& Event)
{
   switch (Event.Type)
   {
      case sf::Event::KeyPressed:
         for (ConType::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->OnKeyDown (Event.Key.Code))
               return true;
               // return true if one of our handlers returned true; ie the event was eaten
      break;

      case sf::Event::Resized:
         for (ConType::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            (*i)->OnResize (Vector2i(Event.Size.Width, Event.Size.Height));
               // We want all event handlers to receive this one; we don't want it to be "eaten"
      break;

      case sf::Event::KeyReleased:
         for (ConType::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->OnKeyUp (Event.Key.Code))
               return true;
      break;

      case sf::Event::MouseButtonPressed:
         for (ConType::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->OnMouseDown (Event.MouseButton.Button, Vector2i(mpInput->GetMouseX (), mpInput->GetMouseY ()), Vector2i(mpInput->GetMouseX (), mpInput->GetMouseY ())))
               return true;
      break;

      case sf::Event::MouseButtonReleased:
         for (ConType::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->OnMouseUp (Event.MouseButton.Button, Vector2i(mpInput->GetMouseX (), mpInput->GetMouseY ()), Vector2i(mpInput->GetMouseX (), mpInput->GetMouseY ())))
               return true;
      break;

      case sf::Event::MouseMoved:
         for (ConType::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->OnMouseMove (Vector2i(mpInput->GetMouseX (), mpInput->GetMouseY ()), Vector2i(mpInput->GetMouseX (), mpInput->GetMouseY ())))
               return true;
      break;

      case sf::Event::Closed: {
         // Throw a segfault to get a stack trace.
         /*std::cout << "Closing!\n";
         int* blah;
         blah = '\0';
         int blahah = *blah;*/
         for (ConType::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            (*i)->OnClose ();
               //return true;
         break;
      }

      case sf::Event::MouseWheelMoved:
         for (ConType::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->OnMouseWheel (Event.MouseWheel.Delta))
               return true;
      break;

      // EXTREMELY HACKISH, we need a new way to do this. CUSTOM EVENTS!!!
      case sf::Event::JoyButtonPressed: // no event mutations
         for (ConType::iterator i = mHandlers.begin (); i != mHandlers.end (); i++)
            if ((*i)->OnToolHit("DOESNT WORK YET DUH!!!!")) // event does not support other events
               return true;

      default:
         return false;
      break;
   }
   return false;
}
