/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include <algorithm>
#include "ActionParameter.hpp"

namespace JEBBase { namespace StateMachine {

template <typename State, typename Event, typename Data>
StateMachine<State, Event, Data>::StateMachine()
    : m_State(),
      m_Data(),
      m_Dirty(false)
{}

template <typename State, typename Event, typename Data>
StateMachine<State, Event, Data>::StateMachine(
            std::vector<TransitionType> transitions,
            const State& initialState)
    : m_State(initialState),
      m_Transitions(move(transitions)),
      m_Data(),
      m_Dirty(!m_Transitions.empty())
{}

template <typename State, typename Event, typename Data>
StateMachine<State, Event, Data>::StateMachine(
            std::vector<TransitionType> transitions,
            const State& initialState,
            const Data& data)
    : m_State(initialState),
      m_Transitions(move(transitions)),
      m_Data(data),
      m_Dirty(!m_Transitions.empty())
{}

template <typename State, typename Event, typename Data>
const State& StateMachine<State, Event, Data>::state() const
{
    return m_State;
}

template <typename State, typename Event, typename Data>
void StateMachine<State, Event, Data>::setState(const State& state)
{
    m_State = state;
}

template <typename State, typename Event, typename Data>
void StateMachine<State, Event, Data>::addTransition(const TransitionType& transition)
{
    m_Dirty = m_Dirty ||
              (!m_Transitions.empty() && transition < m_Transitions.back());
    m_Transitions.push_back(transition);
}

template <typename State, typename Event, typename Data>
auto StateMachine<State, Event, Data>::transition(const Event& event)
        -> const TransitionType*
{
    ensureValidState();
    typename std::vector<TransitionType>::const_iterator it =
                std::lower_bound(m_Transitions.begin(), m_Transitions.end(),
                                 TransitionType(m_State, event));
    if (it != m_Transitions.end()
        && it->fromState() == m_State
        && it->event() == event)
        return &(*it);
    else
        return NULL;
}

template <typename State, typename Event, typename Data>
Data& StateMachine<State, Event, Data>::data()
{
  return m_Data;
}

template <typename State, typename Event, typename Data>
const Data& StateMachine<State, Event, Data>::data() const
{
  return m_Data;
}

template <typename State, typename Event, typename Data>
void StateMachine<State, Event, Data>::setData(const Data& data)
{
  m_Data = data;
}

template <typename State, typename Event, typename Data>
bool StateMachine<State, Event, Data>::event(const Event& event)
{
    const TransitionType* tran = transition(event);
    if (!tran)
        throw std::invalid_argument("No rule defined for current state and given event");

    bool result = true;
    if (tran->action())
    {
        ActionParameterType param(tran, this);
        result = tran->action()(param);
        m_State = param.nextState();
    }
    else
    {
        m_State = tran->toState();
    }

    return result;
}

template <typename State, typename Event, typename Data>
void StateMachine<State, Event, Data>::ensureValidState()
{
    if (m_Dirty)
    {
        std::sort(m_Transitions.begin(), m_Transitions.end());
        m_Dirty = false;
    }
}

}}
