/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_STATEMACHINE_STATEMACHINE_HPP
#define JEBBASE_STATEMACHINE_STATEMACHINE_HPP

#include <functional>
#include <vector>
#include "Transition.hpp"

namespace JEBBase { namespace StateMachine {

template <typename State, typename Event>
class StateMachine
{
public:
    typedef State StateType;
    typedef Event EventType;
    typedef Transition<State, Event> TransitionType;
    typedef ActionParameter<State, Event> ActionParameterType;
    typedef std::function<bool (ActionParameterType&)> ActionType;

    StateMachine();
    StateMachine(const std::vector<Transition<State, Event>>& transitions,
                 const State& initialState);

    const State& state() const;
    void setState(const State& state);

    void addTransition(const Transition<State, Event>& transition);
    const Transition<State, Event>* transition(const Event& event);

    bool event(const Event& event);
private:
    void ensureValidState();

    State m_State;
    std::vector<Transition<State, Event>> m_Transitions;
    mutable bool m_Dirty;
};

}}

#include "StateMachine_impl.hpp"

#endif
