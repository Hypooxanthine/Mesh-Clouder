#pragma once

#include "Data/Mesh.h"
#include "Data/Ray.h"
#include "Data/HitResult.h"

#include <glm/glm.hpp>

class PointCloud;

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

    /**
     * @brief Returns a rotation matrix M so that M * "from" is aligned with "to".
     * 
     * @param from The vector to align
     * @param to The target vector
     * @return glm::mat4 Rotation to apply to "from" so that its aligned with "to"
     */
    static glm::mat4 AlignVectors(const glm::vec3& from, const glm::vec3& to);
    
    static void SampleTriangle(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, PointCloud& data, unsigned int samples);

    static void SampleTriangleRecursive(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, PointCloud& data, unsigned int samples);
};