#pragma once

class State
{
public:
    State() = default;
    virtual ~State() = default;

    virtual void update() {}
    virtual void render() {}
    virtual void renderImGui() {}

private:

};