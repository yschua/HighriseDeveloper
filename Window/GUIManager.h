#ifndef GUIManager_H
#define GUIManager_H

#include <CEGUI.h>

#include <RendererModules/OpenGLGUIRenderer/openglrenderer.h>
#include <CEGUISystem.h>
#include <CEGUIDefaultResourceProvider.h>
#include "Event.h"
#include <iostream>

class SceneEvent;
class FloorBase;
class Tower;


class GUIManager : public EventBase
{
public:
	GUIManager(SceneEvent& rse); //, Tower* Tower);
	~GUIManager();

   bool OnOffice (const CEGUI::EventArgs& e);   // concrete until we setup registering the rooms
   bool OnApartment (const CEGUI::EventArgs& e);
   bool OnStairs (const CEGUI::EventArgs& e);
   bool OnOpen (const CEGUI::EventArgs& e);
   bool OnSave (const CEGUI::EventArgs& e);
   // OnSelect  use this to set the option select rooms for info and to expand the lobby and elevators

	//bool Initialize(sf::RenderWindow* Win);
   bool OnMouseDown (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam);
   bool OnMouseUp (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam);
   bool OnKeyDown (sf::Key::Code Key);
   bool OnKeyUp (sf::Key::Code Key);
   bool OnMouseMove (Vector2i Scene, Vector2i Cam);
   bool OnMouseWheel (int Delta);
   bool OnResize (Vector2i NewSize);
	void Draw();

	CEGUI::System* getSystem() { return mpSystem; }
	CEGUI::WindowManager* getWindowManager() { return mpWM; }
	void setRootWindow(CEGUI::Window* Win) {mpSystem->setGUISheet(Win); mpRootWind = Win;}
	CEGUI::Window* LoadLayout(const std::string& Name);
	CEGUI::Window* LoadLayout(const std::string& Name, CEGUI::Window* Parent);

private:

	CEGUI::System* mpSystem;
	CEGUI::OpenGLRenderer* mpRenderer;
	CEGUI::WindowManager* mpWM;
	CEGUI::Window* mpRootWind;

	typedef std::map<sf::Key::Code, CEGUI::Key::Scan> KeyMap;
	typedef std::map<sf::Mouse::Button, CEGUI::MouseButton> MouseButtonMap;

	KeyMap mKeyMap;
	MouseButtonMap mMouseButtonMap;
	bool mPlacingRoom;
	FloorBase* mRoom;

   SceneEvent& mSE;  // this does not belong here but needed until the event manager can hande it

	void InitMaps();
	CEGUI::Key::Scan CEKey(sf::Key::Code Code);
	CEGUI::MouseButton CEMouseButton(sf::Mouse::Button Button);
};

#endif
