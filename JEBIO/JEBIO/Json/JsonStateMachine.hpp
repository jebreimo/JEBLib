#ifndef JEB_JSON_STATEMACHINE_HPP
#define JEB_JSON_STATEMACHINE_HPP

#include <JEB/StateMachine/StateMachine.hpp>
#include "JsonValue.hpp"

namespace JEB { namespace Json {

namespace State
{
    enum Type
    {
        InitialState,
        AfterKey,
        AfterComma,
        AfterStartObject,
        AfterStartList,
        AfterColon,
        AfterValue,
        EndState
    };
    std::string toString(Type value);
    Type fromString(const std::string& str);
}

namespace Event
{
    enum Type
    {
        BeginObject,
        EndObject,
        BeginArray,
        EndArray,
        StringValue,
        Value,
        Comma,
        Colon,
        InvalidToken,
        EndOfFile
    };
    std::string toString(Type value);
    Type fromString(const std::string& str);
}

class StateMachineActions
{
public:
    typedef StateMachine::StateMachine<State::Type, Event::Type> StateMachine;
    typedef JsonStateMachine::TransitionType Transition;
    typedef JsonStateMachine::ActionParameterType ActionParameter;

    // StateMachineActions();
    bool beginObject(const ActionParameter& param);
    bool endObject(const ActionParameter& param);
    bool beginArray(const ActionParameter& param);
    bool endArray(const ActionParameter& param);
    // bool key(const ActionParameter& param);
    // bool stringValue(const ActionParameter& param);
private:
    JsonValue* m_RootValue;
    std::stack<JsonValue*> m_Values;
    JsonObject* m_CurrentObject;
    JsonArray* m_CurrentArray;
};

}}

#endif
