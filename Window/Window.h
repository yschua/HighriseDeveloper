#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>

#include "../Graphics/Graphics.h"
//#include "../Input/Input.h"
//#include "../Game/Cursor.h"
#include "Element.h"
#include "../highrisedev.h"

namespace hr {
    /// Code for window, and element management, as well as anything else you can think of.
    /// Asfar as i know, this all has to be in the header file because of compiler limitations
    /// when using templates.
    //template <class T, class FocusBehaviour> class EventMgr;
    //template <class T>
    //class ClickToFocus {
    //    public:
    //    void MouseOverNoT(EventMgr<T, ClickToFocus<T> >* Mgr) {
    //        Mgr->ActiveT = NULL;
    //        for (Mgr::IterType iter = Mgr->Ts.begin(); iter != Mgr->Ts.end(); iter++) (**iter).DeActivate();
    //    }
    //}
    template <class T>
    class EventMgr {
        public:
        EventMgr() {
            ActiveT = NULL;
            Disabled = false;
            mpCamera = C_Camera::GetInstance();
        }
        ~EventMgr() {
            IterType iter;
            for (iter = Ts.begin(); iter != Ts.end(); iter++) {
                delete *iter;
            }
            delete this;
        }
        void Add(T* ToAdd) {
            Ts.push_back(ToAdd);
        }
        void Insert(T* ToInsert, int Position) {
            // Not working... i think there is a silly mistake. If someone wants to fix it, go ahead.
            //std::vector<T*>::iterator iter;
            //iter = Ts.begin();
            //iter += Position;
            //Ts.insert(iter, ToInsert);
        }
        void Update() {
            IterType iter;
            for (iter = Ts.begin(); iter != Ts.end(); iter++) {
                (**iter).Update();
            }
        }
        void Draw() {
            typename std::list<T*>::reverse_iterator iter;
            //mpCamera->SetStatic(true);
            for (iter = Ts.rbegin(); iter != Ts.rend(); ++iter) {
                //std::cout << i << "\n";
                (**iter).Draw();
            }
            //mpCamera->SetStatic(false);
        }
        void Disable() {
            Disabled = true;
            IterType iter;
            for (iter = Ts.begin(); iter != Ts.end(); iter++) {
                (**iter).Disable();
            }
        }
        // Handling events... The most recently active item receives events.
        bool OnEvent(const sf::Event& Event) {
            if (Disabled) return false;
            if (Event.Type == sf::Event::MouseMoved ||
                Event.Type == sf::Event::MouseButtonPressed) {
                    /*if (ActiveT != NULL) {
                        Gfx::Cur.SetType("Default");
                    }*/
                    std::cout << "ActiveT: " << ActiveT << "  MousedT: " << MousedT << "\n";
                    // Does the currently "active" window contain the mouse?

                    if (Event.Type == sf::Event::MouseButtonPressed) {
                        if (ActiveT) {
                            if (ActiveT->Contains(mpCamera->GetLocalMouse())) {
                                return ActiveT->OnEvent(Event);
                            }
                        }
                    } else {
                        if (MousedT) {
                            if (MousedT->Contains(mpCamera->GetLocalMouse())) {
                                return MousedT->OnEvent(Event);
                            }
                        }
                    }
                    // Guess not, we'll have to find one that does
                    IterType iter;
                    for (iter = Ts.begin(); iter != Ts.end(); iter++) {
                        // Does this one contain it?
                        if ((**iter).Contains(mpCamera->GetLocalMouse())) {
                            // Deactivate the previously active window
                            if (Event.Type == sf::Event::MouseButtonPressed) {
                                if (ActiveT) ActiveT->DeActivate();
                                //ActiveT = NULL;
                                ActiveT = *iter;
                                ActiveT->Activate();
                                // Move the newly activated window to the front of the list
                                std::swap(*iter, *Ts.begin());
                            } else {
                                if (MousedT) MousedT->MouseOut();
                                //MousedT = NULL;
                                MousedT = *iter;
                                MousedT->MouseIn();
                            }
                            if (ActiveT) ActiveT->OnEvent(Event);
                            //else std::cout << "ActiveT is NULL!\n";
                            return true;
                        }
                    }
                    // None of the windows contained the mouse
                    if (Event.Type == sf::Event::MouseButtonPressed) {
                        if (ActiveT) {
                            ActiveT->DeActivate();
                            ActiveT = NULL;
                        }
                    } else {
                        if (MousedT) {
                            MousedT->MouseOut();
                            MousedT = NULL;
                        }
                    }
                } else {
                    if (ActiveT) return ActiveT->OnEvent(Event);
                }
            return false;
        }
        private:
        typedef typename std::list<T*>::iterator IterType;
        T* ActiveT;
        T* MousedT;
        std::list<T*> Ts;
        bool Disabled;
        C_Camera* mpCamera;
    };
    class WindowStyle {
        public:
        WindowStyle();
        virtual ~WindowStyle();
        bool Resizable;
        bool Titlebar;
        bool Activated;
        sf::Color ActiveColor;
        // MouseOverColor is added to the other color to get the final color, where the other color
        // is ActiveColor for an active window, or InActiveColor for an inactive window.
        sf::Color MouseOverColor;
        sf::Color InActiveColor;
        sf::Color DisabledColor;
        int Padding [5];
        float FontSize;
        //sf::Color CurrentColor; // Don't modify this one!
    };
    class Window {
        public:
        Window();
        virtual ~Window();
        Window operator=(const Window& CopyFrom);
        void SetStyle(WindowStyle NewStyle);
        WindowStyle GetStyle();
        void SetCaption(std::string NewCaption);
        void Update();
        void Draw();
        void Disable();
        void Activate();
        void DeActivate();
        void MouseIn();
        void MouseOut();
        void SetColor();
        void AddItem(UI::Element* ToAdd);
        bool OnEvent(const sf::Event& Event);
        const sf::Rect<int>& GetRect();
        bool Contains(Vector2i Mouse);
        private:
        EventMgr<UI::Element> Items;
        //std::vector<UI::Element*> Items;
        WindowStyle Style;
        sf::Rect<int> Rect;
        sf::Rect<int> InsideRect;
        sf::Rect<int> TitleRect;
        bool Disabled;
        bool Resized;
        bool Resizing;
        bool Moving;
        bool MouseOver;
        std::string ResizingDir;
        bool Activated;
        sf::String Title;
        std::vector<sf::Sprite> BGImgs;
        sf::Vector2<int> MouseStartPosition;
        std::string  ResizeDirection(Vector2i Mouse);
        C_Camera* mpCamera;
        //unsigned int ActiveElement;
    };

}
