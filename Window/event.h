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

#ifndef _EVENT_H
#define _EVENT_H

#include "../Types/Vector2.h"
class Camera;

class EventBase
{
public:
   virtual bool Resize (Vector2i viewSize) { return false; }
   virtual bool MouseDown (sf::Mouse::Button Button, Vector2i World, Vector2i Cam) { return false; }
   virtual bool MouseUp (sf::Mouse::Button Button, Vector2i World, Vector2i Cam) { return false; }
   virtual bool KeyDown (sf::Key::Code Key) { return false; }
   virtual bool KeyUp (sf::Key::Code Key) { return false; }
   virtual bool MouseMove (Vector2i World, Vector2i Cam) { return false; }
   virtual bool MouseWheel (int Delta) { return false; }
   virtual bool Close () { return false; }
};

class EventHandler
{
private:
   typedef std::vector<EventBase*> ConType;
   ConType mHandlers;
   Camera* Cam;
   const sf::Input* mpInput;

public:
   EventHandler ();
   void Add (EventBase* Handler);
   bool HandleEvents (const sf::Event& Event);
};

#endif // _EVENT_H
