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
