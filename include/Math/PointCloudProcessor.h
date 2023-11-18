#pragma once

#include <cstdint>
#include <random>

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
    PointCloudProcessor();
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
    void setSeed(uint32_t seed);

    float getDensity() const;
    const glm::vec3& getMinDisturb() const;
    const glm::vec3& getMaxDistrub() const;

private:
    /* Helper functions */
    void processTriangle(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, PointCloud& output) const;

private:
    /* Processing settings */

    // Density
    float m_PointGap = 1.f;

    // Disturbances
    mutable std::mt19937 m_RandomGenerator;
    glm::vec3 m_MinDisturb, m_MaxDisturb;
};
