#ifndef GUIManager_H
#define GUIManager_H

#include <CEGUI.h>
#include <RendererModules/OpenGLGUIRenderer/openglrenderer.h>
#include <CEGUISystem.h>
#include <CEGUIDefaultResourceProvider.h>
#include "event.h"
#include <iostream>

class SceneEvent;
class FloorBase;
class Tower;


class GUIManager : public EventBase
{
public:
	GUIManager(SceneEvent& rse, Tower* Tower);
	~GUIManager();

   bool OnOffice (const CEGUI::EventArgs& e);

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
	//sf::RenderWindow* mpWindow;
	//const sf::Input* mpInput;

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
	Tower* mTower;

   //SceneEvent& mSE;  // this does not belong here but needed until the event manager can hande it

	void InitMaps();
	CEGUI::Key::Scan CEKey(sf::Key::Code Code);
	CEGUI::MouseButton CEMouseButton(sf::Mouse::Button Button);
};

#endif
