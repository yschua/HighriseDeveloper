#include <SFML/System.hpp>
#include <string>
#include <CEGUI/CEGUI.h>
//#include <json/json.h>

#include "../Root/HighRiseException.h"

#include "../Root/SceneEvent.h"
#include "SettingsWindow.h"
#include "GUIManager.h"


GUIManager::GUIManager(SceneEvent& rse, Interface& rInterface) //, Tower* Tower) can't pass a tower as there will be more than one. Think events
:  mpRenderer(NULL)
,  mpSystem(NULL)
,  mSE(rse)
,  mInterface(rInterface)
{
   mpPrefsWin = NULL;
	InitMaps();
	try
	{
	   using namespace CEGUI;
	   // LOOK, we are USING THE CEGUI NAMESPACE!! The extra CEGUI::'s are not nessesary...
      mpRenderer = &OpenGLRenderer::create();
      mpSystem = &System::create(*mpRenderer);
      DefaultResourceProvider* rp = static_cast<DefaultResourceProvider*>
         (System::getSingleton().getResourceProvider());

      rp->setResourceGroupDirectory("resource", "data/gui/");
      ImageManager::setImagesetDefaultResourceGroup("resource");
      Font::setDefaultResourceGroup("resource");
      Scheme::setDefaultResourceGroup("resource");
      WidgetLookManager::setDefaultResourceGroup("resource");
      WindowManager::setDefaultResourceGroup("resource");

      SchemeManager::getSingleton().createFromFile("WindowsLook.scheme");
      FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

		mpWM = WindowManager::getSingletonPtr();

      mpRootWind = mpWM->createWindow( "DefaultWindow", "root" );
      CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(mpRootWind);
      mpRootWind->setMousePassThroughEnabled(true);

      //FontManager::getSingletonPtr()->getFont("DejaVuSans-10.font")->setAutoScaled(false);

      // Just making a test window now
      /*FrameWindow* fWnd = (FrameWindow*) mpWM->createWindow( "WindowsLook/FrameWindow", "testWindow" );
      mpRootWind->addChildWindow( fWnd );
      Window* pTestBtn = mpWM->createWindow("WindowsLook/Button", "TestBtn" );
		pTestBtn->setSize(UVector2(UDim(0.5f, 0), UDim(0.5f, 0)));
		pTestBtn->setPosition(UVector2(UDim(0.25f, 0), UDim(0.4f, 0)));
      fWnd->addChildWindow( pTestBtn );*/

      // JSON test code
      //Json::Value root;
      //Json::Reader reader;
      //std::ifstream conffile;
      //conffile.open("data/gui/Gui.js");
      //if (!conffile.is_open()) { std::cout << "Error loading data/gui/Gui.js! Failed to open file."; }
      //std::string conf;
      //getline(conffile, conf, '\0');
      //std::cout << conf;
      //bool parseGood = reader.parse(conf, root);
      //if (!parseGood) std::cout << "failed to parse /data/gui/Gui.js, " << reader.getFormatedErrorMessages();

      //struct Local {
      //   CEGUI::WindowManager* mpWM;
      //   CEGUI::Window* mpRootWind;
      //   void ProcessNode(Json::Value& Node) {
      //      std::string Name = Node["Name"].asString();
      //      std::string Type = Node["Type"].asString();
      //      Window* NewWindow = mpWM->createWindow(Type, Name);
      //      mpRootWind->addChildWindow(NewWindow);
      //      std::string Size = Node["UnifiedSize"].asString();
      //      NewWindow->setProperty("UnifiedSize", Size);
      //      std::cout << "created window " << Name << " (type " << Type << ") with size " << Size << '\n';
      //      Json::Value children = Node["Children"];
      //      if (children.type()) {
      //         for (int i = 0; i < children.size(); ++i) {
      //            std::cout << children[i];
      //            ProcessNode(children[i]);
      //         }
      //      }
      //   }
      //};
      //Local blah;
      //blah.mpWM = mpWM;
      //blah.mpRootWind = mpRootWind;
      //blah.ProcessNode(root);



      // NOTE getChild() here may or may not return the Window pointer correctly
      // Load the menu layout from xml and get the buttons to do something. NOTE: If you remove the buttons
      // from the xml, this may or may not crash. We need to check if getWindow() returns a vaild pointer.
      CEGUI::Window* pLayout = LoadLayout("Menu.layout");
      pLayout->getChild((utf8*)"BnSelect")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&GUIManager::OnSelect, this));
      pLayout->getChild((utf8*)"BuildBackground/BnOffice")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&GUIManager::OnOffice, this));
      pLayout->getChild((utf8*)"BuildBackground/BnApartment")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&GUIManager::OnApartment, this));
      pLayout->getChild((utf8*)"BuildBackground/BnHotel")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&GUIManager::OnHotel, this));
      pLayout->getChild((utf8*)"BuildBackground/BnHousekeeping")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&GUIManager::OnHousekeeping, this));
      pLayout->getChild((utf8*)"BuildBackground/BnSecurity")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&GUIManager::OnSecurity, this));
      pLayout->getChild((utf8*)"BuildBackground/BnClinic")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&GUIManager::OnClinic, this));
      pLayout->getChild((utf8*)"BuildBackground/BnCondo")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&GUIManager::OnCondo, this));
      pLayout->getChild((utf8*)"BuildBackground/BnStairs")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&GUIManager::OnStairs, this));
      // elevator
      pLayout->getChild((utf8*)"Open")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&GUIManager::OnOpen, this));
      pLayout->getChild((utf8*)"Save")->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&GUIManager::OnSave, this));

      CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("WindowsLook/MouseArrow");
	}
	catch (CEGUI::Exception& e)
	{
      throw new HighriseException(e.getMessage().c_str());
	}
}

GUIManager::~GUIManager()
{
    CEGUI::System::destroy();
    CEGUI::OpenGLRenderer::destroy(*mpRenderer);
}

void GUIManager::setRootWindow(CEGUI::Window* Win)
{
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(Win);
    mpRootWind = Win;
}

CEGUI::Window* GUIManager::LoadLayout(const std::string& Name) {
   return LoadLayout(Name, mpRootWind);
}

CEGUI::Window* GUIManager::LoadLayout(const std::string& Name, CEGUI::Window* Parent) {
   CEGUI::Window* pLayout = mpWM->loadLayoutFromFile(Name);
   Parent->addChild(pLayout);
   return pLayout;
}

void GUIManager::Draw()
{
    CEGUI::System::getSingleton().renderAllGUIContexts();
}

/* Handling events... */
bool GUIManager::OnSelect (const CEGUI::EventArgs& e)
{
   // set FloorPlacement to Office
   // route mouse clicks that hit the main into the FloorPlacement manager.
   if (!mpPrefsWin)
   {
      mpPrefsWin = new SettingsWindow(mInterface);
   }
   mpPrefsWin->Create (this->mpRootWind);
   mSE.OnToolHit (HR_SelectBuildCursor);  // this only sets the strategy.
   return true;
}


bool GUIManager::OnOffice (const CEGUI::EventArgs& e)
{
   // set FloorPlacement to Office
   // route mouse clicks that hit the main into the FloorPlacement manager.
   mSE.OnToolHit (HR_PlaceOffice);  // this only sets the strategy.
   return true;
}

bool GUIManager::OnApartment (const CEGUI::EventArgs& e)
{

   // set FloorPlacement to Apartment
   // route mouse clicks that hit the main into the FloorPlacement manager.
   mSE.OnToolHit (HR_PlaceApartment);  // this only sets the strategy.
   return true;
}

bool GUIManager::OnCondo (const CEGUI::EventArgs& e)
{

   // set FloorPlacement to Stairs
   // route mouse clicks that hit the main into the FloorPlacement manager.
   mSE.OnToolHit (HR_PlaceCondo);  // this only sets the strategy.
   return true;
}

bool GUIManager::OnHotel (const CEGUI::EventArgs& e)
{

   // set FloorPlacement to Stairs
   // route mouse clicks that hit the main into the FloorPlacement manager.
   mSE.OnToolHit (HR_PlaceHotelSingle);  // this only sets the strategy.
   return true;
}

bool GUIManager::OnRetail (const CEGUI::EventArgs& e)
{

   // set FloorPlacement to Stairs
   // route mouse clicks that hit the main into the FloorPlacement manager.
   mSE.OnToolHit (HR_PlaceRetail);  // this only sets the strategy.
   return true;
}

bool GUIManager::OnSecurity (const CEGUI::EventArgs& e)
{

   // set FloorPlacement to Stairs
   // route mouse clicks that hit the main into the FloorPlacement manager.
   mSE.OnToolHit (HR_PlaceSecurity);  // this only sets the strategy.
   return true;
}

bool GUIManager::OnHousekeeping (const CEGUI::EventArgs& e)
{

   // set FloorPlacement to Stairs
   // route mouse clicks that hit the main into the FloorPlacement manager.
   mSE.OnToolHit (HR_PlaceHouseKeeping);  // this only sets the strategy.
   return true;
}

bool GUIManager::OnClinic (const CEGUI::EventArgs& e)
{

   // set FloorPlacement to Stairs
   // route mouse clicks that hit the main into the FloorPlacement manager.
   mSE.OnToolHit (HR_PlaceClinic);  // this only sets the strategy.
   return true;
}

bool GUIManager::OnWaste (const CEGUI::EventArgs& e)
{

   // set FloorPlacement to Stairs
   // route mouse clicks that hit the main into the FloorPlacement manager.
   mSE.OnToolHit (HR_PlaceWasteManagement);  // this only sets the strategy.
   return true;
}

bool GUIManager::OnElevator (const CEGUI::EventArgs& e)
{

   // set FloorPlacement to Stairs
   // route mouse clicks that hit the main into the FloorPlacement manager.
   mSE.OnToolHit (HR_PlaceStairs);  // this only sets the strategy.
   return true;
}

bool GUIManager::OnStairs (const CEGUI::EventArgs& e)
{

   // set FloorPlacement to Stairs
   // route mouse clicks that hit the main into the FloorPlacement manager.
   mSE.OnToolHit (HR_PlaceStairs);  // this only sets the strategy.
   return true;
}

bool GUIManager::OnRemove (const CEGUI::EventArgs& e)
{

   // set FloorPlacement to Stairs
   // route mouse clicks that hit the main into the FloorPlacement manager.
   mSE.OnToolHit (HR_PlaceStairs);  // this only sets the strategy.
   return true;
}

bool GUIManager::OnOpen(const CEGUI::EventArgs& e)
{
   // Should display a dialog asking the user what they want to open.
   // But, we need a way to do this, and a way to pause the game when we do.
   mSE.OnOpen("data/xml/Tower.xml");
   return true;
}

bool GUIManager::OnSave(const CEGUI::EventArgs& e)
{
   // Should display a dialog asking the user where they want to save.
   // But, we need a way to do this, and a way to pause the game when we do.
   // Should this be moved elsewhere?
   mSE.OnSave("data/xml/Tower2.xml");
   return true;
}

bool
GUIManager::OnMouseDown (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam)
{
   // remember, this is just the GUI code, mouse downs for the tower are passed through to the 3D system
   //// SUPERULTRABUGGYFANTASTIC atm.
   //if (mPlacingRoom || mRoom) {
   //   std::cout << "This part should place the room!\n";
   //   mRoom->SetX(Scene.x);
   //   mRoom->SetY(1);
   //   mTower->GetLevel(1)->AddFloor(mRoom);
   //   //mTower.AddRoom(mRoom);
   //   mPlacingRoom = false;
   //   mRoom = NULL;
   //} else {
      return CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEMouseButton(Button));
   //}
}

bool
GUIManager::OnMouseUp (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam)
{
    return CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEMouseButton(Button));
}

bool
GUIManager::OnKeyDown (sf::Keyboard::Key Key)
{
    return CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(CEKey(Key));
}

bool
GUIManager::OnKeyUp (sf::Keyboard::Key Key)
{
    return CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(CEKey(Key));
}

bool
GUIManager::OnMouseMove (Vector2i Scene, Vector2i Cam)
{
    return CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(static_cast<float>(Cam.x), static_cast<float>(Cam.y));
}

bool
GUIManager::OnMouseWheel (int Delta)
{
   if (CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseWheelChange(static_cast<float>(Delta))) {
      std::cout << "GUIManager ate MouseWheel (OMNOMNOM now make me a sandwich)" << std::endl;
      return true;
   }
   else
      return false;
}

bool GUIManager::OnResize(Vector2i NewSize)
{
   // We need to manually resize the space the GUI is being drawn on so that things are not streched.
   // For some reason, this doesn't work.
   //mpRootWind->setSize(CEGUI::UVector2(CEGUI::UDim(0, NewSize.x*10), CEGUI::UDim(1, NewSize.y)));
   mpRenderer->setDisplaySize(CEGUI::Sizef((float)NewSize.x, (float)NewSize.y));
   std::cout << "Set the size of the CEGUI window! (" << NewSize.x << ", " << NewSize.y << ")\n";
   return false;
}



/************************************************************************/
/*                              Private                                 */
/************************************************************************/

CEGUI::Key::Scan
GUIManager::CEKey (sf::Keyboard::Key Code)
{
	if (mKeyMap.find(Code) == mKeyMap.end())
		return (CEGUI::Key::Scan)0;

	return mKeyMap[Code];
}

CEGUI::MouseButton
GUIManager::CEMouseButton (sf::Mouse::Button Button)
{
	if (mMouseButtonMap.find(Button) == mMouseButtonMap.end())
		return (CEGUI::MouseButton)0;

	return mMouseButtonMap[Button];
}

//Auto-generated (phew...), edited by hand
void
GUIManager::InitMaps()
{
	mKeyMap[sf::Keyboard::Escape]          = CEGUI::Key::Escape       ;
	mKeyMap[sf::Keyboard::Num1]            = CEGUI::Key::One          ;
	mKeyMap[sf::Keyboard::Num2]            = CEGUI::Key::Two          ;
	mKeyMap[sf::Keyboard::Num3]            = CEGUI::Key::Three        ;
	mKeyMap[sf::Keyboard::Num4]            = CEGUI::Key::Four         ;
	mKeyMap[sf::Keyboard::Num5]            = CEGUI::Key::Five         ;
	mKeyMap[sf::Keyboard::Num6]            = CEGUI::Key::Six          ;
	mKeyMap[sf::Keyboard::Num7]            = CEGUI::Key::Seven        ;
	mKeyMap[sf::Keyboard::Num8]            = CEGUI::Key::Eight        ;
	mKeyMap[sf::Keyboard::Num9]            = CEGUI::Key::Nine         ;
	mKeyMap[sf::Keyboard::Num0]            = CEGUI::Key::Zero         ;
	mKeyMap[sf::Keyboard::Hyphen]          = CEGUI::Key::Minus        ;
	mKeyMap[sf::Keyboard::Equal]           = CEGUI::Key::Equals       ;
	mKeyMap[sf::Keyboard::Backspace]       = CEGUI::Key::Backspace    ;
	mKeyMap[sf::Keyboard::Tab]             = CEGUI::Key::Tab          ;
	mKeyMap[sf::Keyboard::Q]               = CEGUI::Key::Q            ;
	mKeyMap[sf::Keyboard::W]               = CEGUI::Key::W            ;
	mKeyMap[sf::Keyboard::E]               = CEGUI::Key::E            ;
	mKeyMap[sf::Keyboard::R]               = CEGUI::Key::R            ;
	mKeyMap[sf::Keyboard::T]               = CEGUI::Key::T            ;
	mKeyMap[sf::Keyboard::Y]               = CEGUI::Key::Y            ;
	mKeyMap[sf::Keyboard::U]               = CEGUI::Key::U            ;
	mKeyMap[sf::Keyboard::I]               = CEGUI::Key::I            ;
	mKeyMap[sf::Keyboard::O]               = CEGUI::Key::O            ;
	mKeyMap[sf::Keyboard::P]               = CEGUI::Key::P            ;
	mKeyMap[sf::Keyboard::LBracket]        = CEGUI::Key::LeftBracket  ;
	mKeyMap[sf::Keyboard::RBracket]        = CEGUI::Key::RightBracket ;
	mKeyMap[sf::Keyboard::Enter]           = CEGUI::Key::Return       ;
	mKeyMap[sf::Keyboard::LControl]        = CEGUI::Key::LeftControl  ;
	mKeyMap[sf::Keyboard::A]               = CEGUI::Key::A            ;
	mKeyMap[sf::Keyboard::S]               = CEGUI::Key::S            ;
	mKeyMap[sf::Keyboard::D]               = CEGUI::Key::D            ;
	mKeyMap[sf::Keyboard::F]               = CEGUI::Key::F            ;
	mKeyMap[sf::Keyboard::G]               = CEGUI::Key::G            ;
	mKeyMap[sf::Keyboard::H]               = CEGUI::Key::H            ;
	mKeyMap[sf::Keyboard::J]               = CEGUI::Key::J            ;
	mKeyMap[sf::Keyboard::K]               = CEGUI::Key::K            ;
	mKeyMap[sf::Keyboard::L]               = CEGUI::Key::L            ;
	mKeyMap[sf::Keyboard::Semicolon]       = CEGUI::Key::Semicolon    ;
	mKeyMap[sf::Keyboard::LShift]          = CEGUI::Key::LeftShift    ;
	mKeyMap[sf::Keyboard::Backslash]       = CEGUI::Key::Backslash    ;
	mKeyMap[sf::Keyboard::Z]               = CEGUI::Key::Z            ;
	mKeyMap[sf::Keyboard::X]               = CEGUI::Key::X            ;
	mKeyMap[sf::Keyboard::C]               = CEGUI::Key::C            ;
	mKeyMap[sf::Keyboard::V]               = CEGUI::Key::V            ;
	mKeyMap[sf::Keyboard::B]               = CEGUI::Key::B            ;
	mKeyMap[sf::Keyboard::N]               = CEGUI::Key::N            ;
	mKeyMap[sf::Keyboard::M]               = CEGUI::Key::M            ;
	mKeyMap[sf::Keyboard::Comma]           = CEGUI::Key::Comma        ;
	mKeyMap[sf::Keyboard::Period]          = CEGUI::Key::Period       ;
	mKeyMap[sf::Keyboard::Slash]           = CEGUI::Key::Slash        ;
	mKeyMap[sf::Keyboard::RShift]          = CEGUI::Key::RightShift   ;
	mKeyMap[sf::Keyboard::Multiply]        = CEGUI::Key::Multiply     ;
	mKeyMap[sf::Keyboard::LAlt]            = CEGUI::Key::LeftAlt      ;
	mKeyMap[sf::Keyboard::Space]           = CEGUI::Key::Space        ;
	mKeyMap[sf::Keyboard::F1]              = CEGUI::Key::F1           ;
	mKeyMap[sf::Keyboard::F2]              = CEGUI::Key::F2           ;
	mKeyMap[sf::Keyboard::F3]              = CEGUI::Key::F3           ;
	mKeyMap[sf::Keyboard::F4]              = CEGUI::Key::F4           ;
	mKeyMap[sf::Keyboard::F5]              = CEGUI::Key::F5           ;
	mKeyMap[sf::Keyboard::F6]              = CEGUI::Key::F6           ;
	mKeyMap[sf::Keyboard::F7]              = CEGUI::Key::F7           ;
	mKeyMap[sf::Keyboard::F8]              = CEGUI::Key::F8           ;
	mKeyMap[sf::Keyboard::F9]              = CEGUI::Key::F9           ;
	mKeyMap[sf::Keyboard::F10]             = CEGUI::Key::F10          ;
	mKeyMap[sf::Keyboard::Numpad7]         = CEGUI::Key::Numpad7      ;
	mKeyMap[sf::Keyboard::Numpad8]         = CEGUI::Key::Numpad8      ;
	mKeyMap[sf::Keyboard::Numpad9]         = CEGUI::Key::Numpad9      ;
	mKeyMap[sf::Keyboard::Subtract]        = CEGUI::Key::Subtract     ;
	mKeyMap[sf::Keyboard::Numpad4]         = CEGUI::Key::Numpad4      ;
	mKeyMap[sf::Keyboard::Numpad5]         = CEGUI::Key::Numpad5      ;
	mKeyMap[sf::Keyboard::Numpad6]         = CEGUI::Key::Numpad6      ;
	mKeyMap[sf::Keyboard::Add]             = CEGUI::Key::Add          ;
	mKeyMap[sf::Keyboard::Numpad1]         = CEGUI::Key::Numpad1      ;
	mKeyMap[sf::Keyboard::Numpad2]         = CEGUI::Key::Numpad2      ;
	mKeyMap[sf::Keyboard::Numpad3]         = CEGUI::Key::Numpad3      ;
	mKeyMap[sf::Keyboard::Numpad0]         = CEGUI::Key::Numpad0      ;
	mKeyMap[sf::Keyboard::F11]             = CEGUI::Key::F11          ;
	mKeyMap[sf::Keyboard::F12]             = CEGUI::Key::F12          ;
	mKeyMap[sf::Keyboard::F13]             = CEGUI::Key::F13          ;
	mKeyMap[sf::Keyboard::F14]             = CEGUI::Key::F14          ;
	mKeyMap[sf::Keyboard::F15]             = CEGUI::Key::F15          ;
	mKeyMap[sf::Keyboard::RControl]        = CEGUI::Key::RightControl ;
	mKeyMap[sf::Keyboard::Divide]          = CEGUI::Key::Divide       ;
	mKeyMap[sf::Keyboard::RAlt]            = CEGUI::Key::RightAlt     ;
	mKeyMap[sf::Keyboard::Pause]           = CEGUI::Key::Pause        ;
	mKeyMap[sf::Keyboard::Home]            = CEGUI::Key::Home         ;
	mKeyMap[sf::Keyboard::Up]              = CEGUI::Key::ArrowUp      ;
	mKeyMap[sf::Keyboard::PageUp]          = CEGUI::Key::PageUp       ;
	mKeyMap[sf::Keyboard::Left]            = CEGUI::Key::ArrowLeft    ;
	mKeyMap[sf::Keyboard::Right]           = CEGUI::Key::ArrowRight   ;
	mKeyMap[sf::Keyboard::End]             = CEGUI::Key::End          ;
	mKeyMap[sf::Keyboard::Down]            = CEGUI::Key::ArrowDown    ;
	mKeyMap[sf::Keyboard::PageDown]        = CEGUI::Key::PageDown     ;
	mKeyMap[sf::Keyboard::Insert]          = CEGUI::Key::Insert       ;
	mKeyMap[sf::Keyboard::Delete]          = CEGUI::Key::Delete       ;

	mMouseButtonMap[sf::Mouse::Left]		= CEGUI::LeftButton;
	mMouseButtonMap[sf::Mouse::Middle]		= CEGUI::MiddleButton;
	mMouseButtonMap[sf::Mouse::Right]		= CEGUI::RightButton;
	mMouseButtonMap[sf::Mouse::XButton1]	= CEGUI::X1Button;
	mMouseButtonMap[sf::Mouse::XButton2]	= CEGUI::X2Button;
}
