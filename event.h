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

class EventBase
{
public:
   virtual bool Resize (int x, int y) { return false; }
   virtual bool MouseDown (sf::Mouse::Button Button, int WorldX, int WorldY, int CamX, int CamY) { return false; }
   virtual bool MouseUp (sf::Mouse::Button Button, int WorldX, int WorldY, int CamX, int CamY) { return false; }
   virtual bool KeyDown (sf::Key::Code Key) { return false; }
   virtual bool KeyUp (sf::Key::Code Key) { return false; }
   virtual bool MouseMove (int WorldX, int WorldY, int CamX, int CamY) { return false; }
   virtual bool MouseWheel (int Delta) { return false; }
};

class EventHandler
{
private:
   std::list <EventBase *> mHandlers;
   Camera * Cam;
   const sf::Input * mpInput;

public:
   EventHandler ();
   void Add (EventBase * Handler);
   bool HandleEvents ();
};

#endif // _EVENT_H
