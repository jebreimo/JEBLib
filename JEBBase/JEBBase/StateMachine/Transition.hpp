/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#ifndef JEBBASE_STATEMACHINE_TRANSITION_HPP
#define JEBBASE_STATEMACHINE_TRANSITION_HPP

#include <functional>
#include "Typedefs.hpp"

namespace JEBBase { namespace StateMachine {

template <typename State, typename Event>
class Transition
{
public:
    typedef State StateType;
    typedef Event EventType;
    typedef StateMachine<State, Event> StateMachineType;
    typedef ActionParameter<State, Event> ActionParameterType;
    typedef std::function<bool (ActionParameterType&)> ActionType;

    Transition();
    Transition(const State& fromState, const Event& event);
    Transition(const State& fromState, const Event& event, const State& toState);
    Transition(const State& fromState,
               const Event& event,
               const State& toState,
               const ActionType& action);

    const State& fromState() const;
    void setFromState(const State& fromState);

    const Event& event() const;
    void setEvent(const Event& event);

    const State& toState() const;
    void setToState(const State& toState);

    const ActionType& action() const;
    void setAction(const ActionType& action);
private:
    State m_FromState;
    Event m_Event;
    State m_ToState;
    ActionType m_Action;
};

template <typename State, typename Event>
bool operator<(const Transition<State, Event>& lhs,
               const Transition<State, Event>& rhs);

}}

#include "Transition_impl.hpp"

#endif
