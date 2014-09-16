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

template <typename State, typename Event>
StateMachine<State, Event>::StateMachine()
    : m_State(State()),
      m_Dirty(false)
{
}

template <typename State, typename Event>
StateMachine<State, Event>::StateMachine(
            const std::vector<Transition<State, Event>>& transitions,
            const State& initialState)
    : m_State(State()),
      m_Transitions(transitions),
      m_Dirty(!m_Transitions.empty())
{
}

template <typename State, typename Event>
const State& StateMachine<State, Event>::state() const
{
    return m_State;
}

template <typename State, typename Event>
void StateMachine<State, Event>::setState(const State& state)
{
    m_State = state;
}

template <typename State, typename Event>
void StateMachine<State, Event>::addTransition(const Transition<State, Event>& transition)
{
    m_Dirty = m_Dirty ||
              (!m_Transitions.empty() && transition < m_Transitions.back());
    m_Transitions.push_back(transition);
}

template <typename State, typename Event>
const Transition<State, Event>* StateMachine<State, Event>::transition(const Event& event)
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

template <typename State, typename Event>
bool StateMachine<State, Event>::event(const Event& event)
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

template <typename State, typename Event>
void StateMachine<State, Event>::ensureValidState()
{
    if (m_Dirty)
    {
        std::sort(m_Transitions.begin(), m_Transitions.end());
        m_Dirty = false;
    }
}

}}
