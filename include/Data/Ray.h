#pragma once

#include <glm/glm.hpp>

struct Ray
{
    glm::vec3 origin;
    glm::vec3 direction = {1.f, 0.f, 0.f}; // Null vector wouldn't make any sense
};
