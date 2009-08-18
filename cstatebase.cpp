/*   This file is part of Highrise Developer.
 *
 *   Foobar is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Foobar is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>

#include "cstatebase.h"

void
C_state_base::add_state (int state_num, state_function * function)
{
    m_states[state_num] = function;
}

void
C_state_base::operator() (float dt)
{
    if (m_current_state_function != NULL) {
        int new_state = m_current_state_function (dt);
        if (new_state != m_current_state)
            m_current_state_function = m_states[new_state];
    }
}

void
C_state_base::set_state (int id)
{
    m_current_state = id;
    m_current_state_function = m_states[id];
}
