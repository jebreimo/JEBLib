/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
namespace JEBBase { namespace StateMachine {

template <typename State, typename Event>
Transition<State, Event>::Transition()
    : m_FromState(State()),
      m_Event(Event()),
      m_ToState(State())
{
}

template <typename State, typename Event>
Transition<State, Event>::Transition(const State& fromState,
                                     const Event& event)
    : m_FromState(fromState),
      m_Event(event),
      m_ToState(State())
{
}

template <typename State, typename Event>
Transition<State, Event>::Transition(const State& fromState,
                                     const Event& event,
                                     const State& toState)
    : m_FromState(fromState),
      m_Event(event),
      m_ToState(toState)
{
}

template <typename State, typename Event>
Transition<State, Event>::Transition(const State& fromState,
                                     const Event& event,
                                     const State& toState,
                                     const ActionType& action)
    : m_FromState(fromState),
      m_Event(event),
      m_ToState(toState)
{
}

template <typename State, typename Event>
const State& Transition<State, Event>::fromState() const
{
    return m_FromState;
}

template <typename State, typename Event>
void Transition<State, Event>::setFromState(const State& fromState)
{
    m_FromState = fromState;
}

template <typename State, typename Event>
const Event& Transition<State, Event>::event() const
{
    return m_Event;
}

template <typename State, typename Event>
void Transition<State, Event>::setEvent(const Event& event)
{
    m_Event = event;
}

template <typename State, typename Event>
const State& Transition<State, Event>::toState() const
{
    return m_ToState;
}

template <typename State, typename Event>
void Transition<State, Event>::setToState(const State& toState)
{
    m_ToState = toState;
}

template <typename State, typename Event>
const typename Transition<State, Event>::ActionType&
Transition<State, Event>::action() const
{
    return m_Action;
}

template <typename State, typename Event>
void Transition<State, Event>::setAction(const ActionType& action)
{
    m_Action = action;
}

template <typename State, typename Event>
bool operator<(const Transition<State, Event>& lhs,
               const Transition<State, Event>& rhs)
{
    return lhs.fromState() < rhs.fromState() ||
           (lhs.fromState() == rhs.fromState() && lhs.event() < rhs.event());
}

}}
