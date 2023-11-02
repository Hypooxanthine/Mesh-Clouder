#pragma once

#include <memory>

class State
{
public:
    State();
    virtual ~State() = default;

    /**
     * @brief The update function is for data computing. No rendering is supposed to be done here.
     * 
     */
    virtual void update() {}

    /**
     * @brief The render function is for OpenGL rendering.
     * 
     */
    virtual void render() {}

    /**
     * @brief The renderImGui function is meant for ImGui rendering. ImGui context and frame are already created before this function is called.
     * 
     */
    virtual void renderImGui() {}

    /**
     * @brief When a state has been requested to be killed.
     * 
     * @return true If the state has been killed.
     * @return false Otherwise.
     */
    inline bool isPendingKilled() const { return m_PendingKilled; }

    /**
     * @brief Get the next state as a unique_ptr. The ownership of this pointer is meant to be obtained by the application itself.
     * 
     * @return std::unique_ptr<State>& 
     */
    inline std::unique_ptr<State>& getNextState() { return m_NextState; }

protected:

    /**
     * @brief Kills the state. The next state to be loaded is mandatory.
     * 
     * @param nextState As a raw pointer (new). No delete has to be done : this memory block will be handled by the State class.
     */
    void kill(State* nextState);

private:
    bool m_PendingKilled = false;
    std::unique_ptr<State> m_NextState;
};