#pragma once

#include <glm/glm.hpp>

/**
 * @brief Stores a 2 components vectors.
 * 
 * @tparam T Type of vector's components.
 */
template <typename T>
class Vector2
{
public:
    using Type = T;

public:
    Vector2(const T& x, const T& y) : x(x), y(y) {}
    Vector2() : Vector2(T(0), T(0)) {}

    operator glm::vec2() const
    {
        return glm::vec2((float)x, (float)y);
    }

public:
    T x, y;
};

using Vector2i = Vector2<int>;
using Vector2u = Vector2<unsigned int>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;

/**
 * @brief Stores a 3 components vectors.
 * 
 * @tparam T Type of vector's components.
 */
template <typename T>
class Vector3
{
public:
    using Type = T;

public:
    Vector3(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}
    Vector3() : Vector3(T(0), T(0), T(0)) {}

    operator glm::vec3() const
    {
        return glm::vec3((float)x, (float)y, (float)z);
    }

public:
    T x, y, z;
};

using Vector3i = Vector3<int>;
using Vector3u = Vector3<unsigned int>;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;