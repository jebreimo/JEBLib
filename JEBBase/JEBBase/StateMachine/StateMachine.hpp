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

template <typename State, typename Event, typename Data>
class StateMachine
{
public:
    typedef State StateType;
    typedef Event EventType;
    typedef Data DataType;
    typedef Transition<State, Event, Data> TransitionType;
    typedef ActionParameter<State, Event, Data> ActionParameterType;
    typedef std::function<bool (ActionParameterType&)> ActionType;

    StateMachine();
    StateMachine(std::vector<TransitionType> transitions,
                 const State& initialState);
    StateMachine(std::vector<TransitionType> transitions,
                 const State& initialState,
                 const Data& data);

    const State& state() const;
    void setState(const State& state);

    void addTransition(const TransitionType& transition);
    const TransitionType* transition(const Event& event);

    Data& data();
    const Data& data() const;
    void setData(const Data& data);

    bool event(const Event& event);
private:
    void ensureValidState();

    State m_State;
    std::vector<TransitionType> m_Transitions;
    Data m_Data;
    mutable bool m_Dirty;
};

}}

#include "StateMachine_impl.hpp"

#endif
