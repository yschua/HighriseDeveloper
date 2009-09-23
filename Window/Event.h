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

enum HR_Events
{
   HR_MouseInScene = 0,       // Generic
   HR_ClickInScene,           // Left Click
   HR_MenuInScene,            // Right Click
   HR_SelectBuildCursor,      // From tools if BuildOption returns true, set cursor and/or status bar to show active tool.
   HR_SelectBuildOption,      // From tools, include Office, Elevater, Condo etc as option param
   HR_PlaceOffice,
   HR_PlaceApartment,
   HR_PlaceCondo,
   HR_PlaceElevator,
   HR_PlaceNone,
   HR_Close
};

class Camera;

class EventBase
{
public:
   // HELP! The Resize() event can not actually be captured by some classes, since they
   // already define a Resize() member funtion. Maybe we should call prefix theese with
   // "On"? (So OnResize(), OnMouseDown(), etc).
   virtual bool OnResize (Vector2i viewSize) { return false; }
   virtual bool OnMouseDown (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam) { return false; }
   virtual bool OnMouseUp (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam) { return false; }
   virtual bool OnKeyDown (sf::Key::Code Key) { return false; }
   virtual bool OnKeyUp (sf::Key::Code Key) { return false; }
   virtual bool OnMouseMove (Vector2i Scene, Vector2i Cam) { return false; }
   virtual bool OnMouseWheel (int Delta) { return false; }
   virtual bool OnClose () { return false; }
   virtual bool OnToolHit (const std::string& Name) {return false; }
   virtual bool OnOpen (const char* pPath) { return false; }
   virtual bool OnSave (const char* pPath) { return false; }
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
