#include "States/State.h"

State::State()
    : m_NextState(nullptr)
{}

void State::kill(State* nextState)
{
    m_PendingKilled = true;
    m_NextState = std::unique_ptr<State>(nextState);
}