#include "JsonStateMachine.hpp"

#include <iostream>

namespace JEB { namespace Json {

bool StateMachineActions::beginObject(const ActionParameter& param)
{
    std::cout << "beginObject\n";
}

bool StateMachineActions::endObject(const ActionParameter& param)
{
    std::cout << "endObject\n";
}

bool StateMachineActions::beginArray(const ActionParameter& param)
{
    std::cout << "beginArray\n";
}

bool StateMachineActions::endArray(const ActionParameter& param)
{
    std::cout << "endArray\n";
}

}}