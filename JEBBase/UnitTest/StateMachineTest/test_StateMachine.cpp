/* JEBBase: generic algorithms and functions
 * Copyright 2014 Jan Erik Breimo
 * All rights reserved.
 *
 * This file is distributed under the BSD License.
 * License text is included with the source distribution.
 */
#include "JEBBase/StateMachine/StateMachine.hpp"

#include <JEBTest/JEBTest.hpp>

using namespace JEBBase::StateMachine;

struct MyAction
{
    MyAction(int fromState, int event, int toState)
        : m_FromState(fromState),
          m_Event(event),
          m_ToState(toState)
    {}

    bool operator()(ActionParameter<int, int>& ap)
    {
        JT_EQUAL(ap.currentState(), m_FromState);
        JT_EQUAL(ap.event(), m_Event);
        JT_EQUAL(ap.nextState(), m_ToState);
        return true;
    }

    int m_FromState;
    int m_Event;
    int m_ToState;
};

void test_StateMachine()
{
    StateMachine<int, int> sm;
    JT_EQUAL(sm.state(), 0);
    sm.addTransition(Transition<int, int>(0, 1, 3, MyAction(0, 1, 3)));
    JT_ASSERT(sm.transition(1));
    JT_ASSERT(sm.event(1));
    JT_EQUAL(sm.state(), 3);
    JT_THROWS(sm.event(10), std::exception);
}

JT_SUBTEST("StateMachine", test_StateMachine);
