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

#ifndef GUIManager_H
#define GUIManager_H

#include <CEGUI/CEGUI.h>
#include <iostream>

#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>
#include <CEGUI/System.h>
#include <CEGUI/DefaultResourceProvider.h>
#include "Event.h"

class SceneEvent;
class FloorBase;
class Tower;
class Interface;
class SettingsWindow;


class GUIManager : public EventBase
{
protected:
   SettingsWindow* mpPrefsWin;
   Interface& mInterface;
public:
	GUIManager(SceneEvent& rse, Interface& pInterface); //, Tower* Tower);
	~GUIManager();

   bool OnOffice(const CEGUI::EventArgs& e);   // concrete until we setup registering the rooms
   bool OnApartment(const CEGUI::EventArgs& e);
   bool OnSelect(const CEGUI::EventArgs& e);
   bool OnCondo(const CEGUI::EventArgs& e);
   bool OnHotel(const CEGUI::EventArgs& e);
   bool OnRetail(const CEGUI::EventArgs& e);
   bool OnSecurity(const CEGUI::EventArgs& e);
   bool OnHousekeeping (const CEGUI::EventArgs& e);
   bool OnClinic(const CEGUI::EventArgs& e);
   bool OnWaste(const CEGUI::EventArgs& e);
   bool OnElevator(const CEGUI::EventArgs& e);
   bool OnStairs(const CEGUI::EventArgs& e);
   bool OnRemove(const CEGUI::EventArgs& e);
   bool OnOpen(const CEGUI::EventArgs& e);
   bool OnSave(const CEGUI::EventArgs& e);
   bool OnPreferences(const CEGUI::EventArgs& e);
   bool OnCloseWindow(const CEGUI::EventArgs& e);
   // OnSelect  use this to set the option select rooms for info and to expand the lobby and elevators

	//bool Initialize(sf::RenderWindow* Win);
   bool OnMouseDown (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam);
   bool OnMouseUp (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam);
   bool OnKeyDown (sf::Keyboard::Key Key);
   bool OnKeyUp (sf::Keyboard::Key Key);
   bool OnMouseMove (Vector2i Scene, Vector2i Cam);
   bool OnMouseWheel (int Delta);
   bool OnResize (Vector2i NewSize);
	void Draw();

	CEGUI::System* getSystem() { return mpSystem; }
	CEGUI::WindowManager* getWindowManager() { return mpWM; }
	void setRootWindow(CEGUI::Window* Win);
	CEGUI::Window* LoadLayout(const std::string& Name);
	CEGUI::Window* LoadLayout(const std::string& Name, CEGUI::Window* Parent);

private:

	CEGUI::System* mpSystem;
	CEGUI::OpenGLRenderer* mpRenderer;
	CEGUI::WindowManager* mpWM;
	CEGUI::Window* mpRootWind;

	typedef std::map<sf::Keyboard::Key, CEGUI::Key::Scan> KeyMap;
	typedef std::map<sf::Mouse::Button, CEGUI::MouseButton> MouseButtonMap;

	KeyMap mKeyMap;
	MouseButtonMap mMouseButtonMap;
	//bool mPlacingRoom;
	//FloorBase* mRoom;

   SceneEvent& mSE;  // this does not belong here but needed until the event manager can hande it

	void InitMaps();
	CEGUI::Key::Scan CEKey(sf::Keyboard::Key Code);
	CEGUI::MouseButton CEMouseButton(sf::Mouse::Button Button);
    void InitLayout();
    void LoadResource();
};

#endif
