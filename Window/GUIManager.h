#ifndef GUIManager_H
#define GUIManager_H

#include <CEGUI.h>
#include <RendererModules/OpenGLGUIRenderer/openglrenderer.h>
#include <CEGUISystem.h>
#include <CEGUIDefaultResourceProvider.h>
#include "event.h"
#include <iostream>

class GUIManager : public EventBase
{
public:
	GUIManager();
	~GUIManager();

	//bool Initialize(sf::RenderWindow* Win);
   bool Resize (Vector2i) { return false; }
   bool MouseDown (sf::Mouse::Button Button, Vector2i World, Vector2i Cam);
   bool MouseUp (sf::Mouse::Button Button, Vector2i World, Vector2i Cam);
   bool KeyDown (sf::Key::Code Key);
   bool KeyUp (sf::Key::Code Key);
   bool MouseMove (Vector2i World, Vector2i Cam);
   bool MouseWheel (int Delta);
	void Draw();

	CEGUI::System* getSystem() {return mpSystem;}
	CEGUI::WindowManager* getWindowManager() {return mpWM;}
	void setRootWindow(CEGUI::Window* Win) {mpSystem->setGUISheet(Win); mpRootWind = Win;}

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

	void InitMaps();
	CEGUI::Key::Scan CEKey(sf::Key::Code Code);
	CEGUI::MouseButton CEMouseButton(sf::Mouse::Button Button);
};

#endif
