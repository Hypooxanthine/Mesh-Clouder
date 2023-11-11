#pragma once

#include "Data/Mesh.h"
#include "Data/Ray.h"
#include "Data/HitResult.h"

#include <glm/glm.hpp>

/**
 * @brief Static functions for maths.
 * 
 */
class Math
{
public:
    static Ray RayUnderCursor(const glm::vec3& cameraPos, const glm::mat4& viewProjection, const glm::vec2& cursorPos, const glm::vec2& viewportSize);
    static HitResult RayCastWithMesh(const Ray& ray, const Mesh& mesh);

    /**
     * @brief This assumes that vectors are collinear.
     * 
     * @param u First vector.
     * @param v Second vector.
     * @return true Same directions.
     * @return false Inverse directions.
     */
    static bool AreVectorsOfSameDirection(const glm::vec3& u, const glm::vec3& v);
};