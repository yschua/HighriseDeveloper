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

// #DEFINES moved to resource.h until we get a platform ind resouce file.

#pragma once
#ifndef _SCENE_EVENT
#define _SCENE_EVENT

#include "../Resources.h"

// Include libraries first
#include "../Window/Event.h" // event base

#include <cstring>
#include <utility>

class Scene;

class SceneEvent : public EventBase
{
protected:
    Scene* mpScene;

public:
    SceneEvent(Scene* pScene);
    ~SceneEvent();

    bool OnToolHit(const int tool);
    bool OnOpen(const char* pPath);
    bool OnSave(const char* pPath);
    virtual bool OnMouseDown(sf::Mouse::Button Button, Vector2i point, Vector2i pointb);
    virtual bool OnMouseMove(Vector2i pointa, Vector2i pointb);
    void LoadWindows();
};

#endif //_SCENE_EVENT