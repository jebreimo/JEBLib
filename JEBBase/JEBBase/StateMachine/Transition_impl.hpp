/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#pragma once

namespace JEBBase { namespace StateMachine {

template <typename State, typename Event, typename Data>
Transition<State, Event, Data>::Transition()
    : m_FromState(),
      m_Event(),
      m_ToState()
{}

template <typename State, typename Event, typename Data>
Transition<State, Event, Data>::Transition(const State& fromState,
                                     const Event& event)
    : m_FromState(fromState),
      m_Event(event),
      m_ToState()
{}

template <typename State, typename Event, typename Data>
Transition<State, Event, Data>::Transition(const State& fromState,
                                     const Event& event,
                                     const ActionType& action)
    : m_FromState(fromState),
      m_Event(event),
      m_ToState(),
      m_Action(action)
{}

template <typename State, typename Event, typename Data>
Transition<State, Event, Data>::Transition(const State& fromState,
                                     const Event& event,
                                     const State& toState)
    : m_FromState(fromState),
      m_Event(event),
      m_ToState(toState)
{}

template <typename State, typename Event, typename Data>
Transition<State, Event, Data>::Transition(const State& fromState,
                                     const Event& event,
                                     const ActionType& action,
                                     const State& toState)
    : m_FromState(fromState),
      m_Event(event),
      m_ToState(toState),
      m_Action(action)
{}

template <typename State, typename Event, typename Data>
const State& Transition<State, Event, Data>::fromState() const
{
    return m_FromState;
}

template <typename State, typename Event, typename Data>
void Transition<State, Event, Data>::setFromState(const State& fromState)
{
    m_FromState = fromState;
}

template <typename State, typename Event, typename Data>
const Event& Transition<State, Event, Data>::event() const
{
    return m_Event;
}

template <typename State, typename Event, typename Data>
void Transition<State, Event, Data>::setEvent(const Event& event)
{
    m_Event = event;
}

template <typename State, typename Event, typename Data>
const State& Transition<State, Event, Data>::toState() const
{
    return m_ToState;
}

template <typename State, typename Event, typename Data>
void Transition<State, Event, Data>::setToState(const State& toState)
{
    m_ToState = toState;
}

template <typename State, typename Event, typename Data>
const typename Transition<State, Event, Data>::ActionType&
Transition<State, Event, Data>::action() const
{
    return m_Action;
}

template <typename State, typename Event, typename Data>
void Transition<State, Event, Data>::setAction(const ActionType& action)
{
    m_Action = action;
}

template <typename State, typename Event, typename Data>
bool operator<(const Transition<State, Event, Data>& lhs,
               const Transition<State, Event, Data>& rhs)
{
    return lhs.fromState() < rhs.fromState() ||
           (lhs.fromState() == rhs.fromState() && lhs.event() < rhs.event());
}

}}
