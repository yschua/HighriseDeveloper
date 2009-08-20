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

#include "highrisedev.h"

C_Tiler::C_Tiler (sf::Image * image, int x, int x2, int y)
{
    m_frame = image;
    m_X = x;
    m_X2 = x2;
    m_Y = y;
    m_ImageSizeX = m_frame->GetWidth();
    m_ImageSizeY = m_frame->GetHeight();
    unsigned int tiled_num = (unsigned int) ((x2 - x) / m_ImageSizeX);
    int part = (int) ((tiled_num * m_ImageSizeX) + x);
    for (int i = 0; i <= tiled_num; i++) {
        C_AnimationSingle * new_tiler_part = new C_AnimationSingle (m_frame);
        m_Sprites.push_back (new_tiler_part);
        new_tiler_part->set_position (m_X + (i * m_ImageSizeX), m_Y);
    }
    C_AnimationSingle * end = m_Sprites[m_Sprites.size () - 1];
    end->SetSubRect (0, 0, x2 - part, m_ImageSizeY);
}
