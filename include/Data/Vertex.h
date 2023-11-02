#pragma once

#include "Vector.h"

/**
 * @brief The Vertex struct is used to represent a vertex in memory. It contains a 3D position,
 * a 3D normal vector, a Texture Coordinates.
 * 
 */
struct Vertex
{
    Vertex(const Vector3f& pos, const Vector3f& n, const Vector2f& tc)
        : position(pos), normal(n), texCoords(tc)
    {}
    Vertex() = default;

    Vector3f position;
    Vector3f normal;
    Vector2f texCoords;
};