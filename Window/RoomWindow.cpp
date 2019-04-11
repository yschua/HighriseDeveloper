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

#include "RoomWindow.h"

#include <CEGUI/Window.h>

#include "../Tower/FloorBase.h"

RoomWindow::RoomWindow() : m_room(nullptr)
{
    const auto root = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
    m_wnd = root->getChild("MenuBackground/RoomWindow");
}

RoomWindow::~RoomWindow() {}

void RoomWindow::Show() { m_wnd->show(); }

void RoomWindow::SetRoom(const FloorBase* room)
{
    m_room = room;
    m_wnd->setText(room->GetName());
}
