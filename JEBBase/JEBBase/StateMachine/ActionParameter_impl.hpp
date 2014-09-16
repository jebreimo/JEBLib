/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "Transition.hpp"

namespace JEBBase { namespace StateMachine {

template <typename State, typename Event>
ActionParameter<State, Event>::ActionParameter(
            const Transition<State, Event>* transition,
            StateMachine<State, Event>* stateMachine)
    : m_CurrentState(transition->fromState()),
      m_Event(transition->event()),
      m_DefaultNextState(transition->toState()),
      m_NextState(transition->toState()),
      m_StateMachine(stateMachine)
{
}

template <typename State, typename Event>
ActionParameter<State, Event>::ActionParameter(
            const State& currentState,
            const Event& event,
            const State& nextState,
            StateMachine<State, Event>* stateMachine)
    : m_CurrentState(currentState),
      m_Event(event),
      m_DefaultNextState(nextState),
      m_NextState(nextState),
      m_StateMachine(stateMachine)
{
}

template <typename State, typename Event>
const State& ActionParameter<State, Event>::currentState() const
{
    return m_CurrentState;
}

template <typename State, typename Event>
void ActionParameter<State, Event>::setCurrentState(const State& currentState)
{
    m_CurrentState = currentState;
}

template <typename State, typename Event>
const Event& ActionParameter<State, Event>::event() const
{
    return m_Event;
}

template <typename State, typename Event>
void ActionParameter<State, Event>::setEvent(const Event& event)
{
    m_Event = event;
}

template <typename State, typename Event>
const State& ActionParameter<State, Event>::defaultNextState() const
{
    return m_DefaultNextState;
}

template <typename State, typename Event>
void ActionParameter<State, Event>::setDefaultNextState(const State& defaultNextState)
{
    m_DefaultNextState = defaultNextState;
}

template <typename State, typename Event>
const State& ActionParameter<State, Event>::nextState() const
{
    return m_NextState;
}

template <typename State, typename Event>
void ActionParameter<State, Event>::setNextState(const State& nextState)
{
    m_NextState = nextState;
}

template <typename State, typename Event>
StateMachine<State, Event>* ActionParameter<State, Event>::stateMachine() const
{
    return m_StateMachine;
}

template <typename State, typename Event>
void ActionParameter<State, Event>::setStateMachine(StateMachine<State, Event>* stateMachine)
{
    m_StateMachine = stateMachine;
}

}}
