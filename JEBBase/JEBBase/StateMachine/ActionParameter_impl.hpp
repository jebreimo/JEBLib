/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "Transition.hpp"

namespace JEBBase { namespace StateMachine {

template <typename State, typename Event, typename Data>
ActionParameter<State, Event, Data>::ActionParameter(
            const Transition<State, Event, Data>* transition,
            StateMachine<State, Event, Data>* stateMachine)
    : m_CurrentState(transition->fromState()),
      m_Event(transition->event()),
      m_DefaultNextState(transition->toState()),
      m_NextState(transition->toState()),
      m_StateMachine(stateMachine)
{}

template <typename State, typename Event, typename Data>
ActionParameter<State, Event, Data>::ActionParameter(
            const State& currentState,
            const Event& event,
            const State& nextState,
            StateMachine<State, Event, Data>* stateMachine)
    : m_CurrentState(currentState),
      m_Event(event),
      m_DefaultNextState(nextState),
      m_NextState(nextState),
      m_StateMachine(stateMachine)
{}

template <typename State, typename Event, typename Data>
const State& ActionParameter<State, Event, Data>::currentState() const
{
    return m_CurrentState;
}

template <typename State, typename Event, typename Data>
void ActionParameter<State, Event, Data>::setCurrentState(const State& currentState)
{
    m_CurrentState = currentState;
}

template <typename State, typename Event, typename Data>
const Event& ActionParameter<State, Event, Data>::event() const
{
    return m_Event;
}

template <typename State, typename Event, typename Data>
void ActionParameter<State, Event, Data>::setEvent(const Event& event)
{
    m_Event = event;
}

template <typename State, typename Event, typename Data>
const State& ActionParameter<State, Event, Data>::defaultNextState() const
{
    return m_DefaultNextState;
}

template <typename State, typename Event, typename Data>
void ActionParameter<State, Event, Data>::setDefaultNextState(const State& defaultNextState)
{
    m_DefaultNextState = defaultNextState;
}

template <typename State, typename Event, typename Data>
const State& ActionParameter<State, Event, Data>::nextState() const
{
    return m_NextState;
}

template <typename State, typename Event, typename Data>
void ActionParameter<State, Event, Data>::setNextState(const State& nextState)
{
    m_NextState = nextState;
}

template <typename State, typename Event, typename Data>
StateMachine<State, Event, Data>* ActionParameter<State, Event, Data>::stateMachine() const
{
    return m_StateMachine;
}

template <typename State, typename Event, typename Data>
void ActionParameter<State, Event, Data>::setStateMachine(StateMachine<State, Event, Data>* stateMachine)
{
    m_StateMachine = stateMachine;
}

}}
