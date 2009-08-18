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
