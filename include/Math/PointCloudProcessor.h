#pragma once

#include <cstdint>

#include <glm/glm.hpp>

#include "Data/Mesh.h"
#include "Data/PointCloud.h"

/**
 * @brief Stores processing parameters and creates a PointCloud object from a Mesh object based on these parameters.
 * 
 */
class PointCloudProcessor
{
public:
    PointCloudProcessor() = default;
    ~PointCloudProcessor() = default;

    /**
     * @brief Creates a PointCloud object from a Mesh object with provided settings.
     * 
     * @param mesh The base mesh.
     * @return PointCloud The created point cloud.
     */
    PointCloud process(const Mesh& mesh) const;

    void setDensity(float d);
    void setMinDisturb(const glm::vec3& d);
    void setMaxDisturb(const glm::vec3& d);

private:
    /* Helper functions */
    void processTriangle(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, PointCloud& output) const;

private:
    /* Processing settings */

    // Density
    float m_PointGap = 1.f;

    // Disturbances
    glm::vec3 m_MinDisturb, m_MaxDisturb;
};
