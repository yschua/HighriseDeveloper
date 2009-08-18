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

#ifndef _CSTATEBASE_H
#define _CSTATEBASE_H

typedef int state_function (float dt);

class C_state_base
{
protected:
    int m_current_state;
    state_function * m_current_state_function;
    std::map<int, state_function *> m_states;
    void add_state (int state_num, state_function * function);
    
public:
    void operator() (float dt);
    void set_state (int id);
};

#endif
