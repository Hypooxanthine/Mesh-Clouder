#pragma once

#include <glm/glm.hpp>

struct HitResult
{
    bool hasHit = false;
    float depth = 0.f;
    glm::vec3 position;
    glm::vec3 normal;
};
