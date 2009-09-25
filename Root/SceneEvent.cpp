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

#include <iostream>

// Then user-defined types
#include "../Scene/Scene.h"
#include "../Graphics/Camera.h"
#include "../Window/Event.h"

#include "GameManager.h" // xml saver
#include "SceneEvent.h"

SceneEvent::SceneEvent(Scene* pScene)
{
   mpScene = pScene;
}


SceneEvent::~SceneEvent ()
{
}

bool
SceneEvent::OnToolHit (int tool)
{
   if( tool > HR_SelectBuildOption && tool < HR_PlaceNone )
      return mpScene->SelectTool (tool);

   return false;
}

bool SceneEvent::OnMouseDown (sf::Mouse::Button Button, Vector2i Scene, Vector2i Cam)
{
   Camera* pCam = Camera::GetInstance();
   int hit = pCam->RenderFramework (mpScene, Scene, 0);
   if( hit )
   {
      mpScene->Hit( hit, Scene );
   }
   return true;
}

bool SceneEvent::OnOpen (const char* pPath)
{
   GameManager tm( *mpScene );
   return tm.LoadGame( pPath );
}

bool SceneEvent::OnSave (const char* pPath)
{
   GameManager tm( *mpScene );
   return tm.SaveGame( pPath );
}
