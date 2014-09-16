/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_STATEMACHINE_ACTIONPARAMETER_HPP
#define JEBBASE_STATEMACHINE_ACTIONPARAMETER_HPP

#include "Typedefs.hpp"

namespace JEBBase { namespace StateMachine {

template <typename State, typename Event>
class ActionParameter
{
public:
    ActionParameter(const Transition<State, Event>* transition,
                    StateMachine<State, Event>* stateMachine);
    ActionParameter(const State& currentState,
                    const Event& event,
                    const State& nextState,
                    StateMachine<State, Event>* stateMachine);

    const State& currentState() const;
    void setCurrentState(const State& currentState);

    const Event& event() const;
    void setEvent(const Event& event);

    const State& defaultNextState() const;
    void setDefaultNextState(const State& defaultNextState);

    const State& nextState() const;
    void setNextState(const State& nextState);

    StateMachine<State, Event>* stateMachine() const;
    void setStateMachine(StateMachine<State, Event>* stateMachine);
private:
    const State& m_CurrentState;
    const Event& m_Event;
    const State& m_DefaultNextState;
    State m_NextState;
    StateMachine<State, Event>* m_StateMachine;
};

}}

#include "ActionParameter_impl.hpp"

#endif
