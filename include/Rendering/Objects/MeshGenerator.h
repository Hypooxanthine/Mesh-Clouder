#pragma once

#include "Data/Mesh.h"

class MeshGenerator
{
public:
    static Mesh GenCircle(unsigned int samples);
    static Mesh GenGrid(const glm::vec2& gridSize, const glm::vec2 tileSize);
};