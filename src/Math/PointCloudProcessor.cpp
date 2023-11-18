#include "Math/PointCloudProcessor.h"

#include "Math/Math.h"

#include <iostream>

PointCloudProcessor::PointCloudProcessor()
    : m_RandomGenerator(std::mt19937::default_seed)
{
    
}

PointCloud PointCloudProcessor::process(const Mesh& mesh) const
{
    PointCloud out;
    
    for(size_t i = 0; i < mesh.getIndicesCount(); i += 3)
    {
        const auto& iA = mesh.getIndices()[i + 0];
        const auto& iB = mesh.getIndices()[i + 1];
        const auto& iC = mesh.getIndices()[i + 2];
        const glm::vec3& A = mesh.getVertices()[iA].position;
        const glm::vec3& B = mesh.getVertices()[iB].position;
        const glm::vec3& C = mesh.getVertices()[iC].position;

        processTriangle(A, B, C, out);
    }

    return out;
}

void PointCloudProcessor::processTriangle(const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, PointCloud& output) const
{
    /* Lengths */

    glm::vec3 AB = B - A;
    glm::vec3 AC = C - A;
    float lAB = glm::length(AB);
    float lAC = glm::length(AC);

    /* All points have the same normal */

    glm::vec3 n = glm::cross(AB, AC);

    /* Local axes */

    // For AB edge
    glm::vec3 x = glm::normalize(AB);
    // For AC edge
    glm::vec3 y = glm::normalize(AC);

    /* x and y progress */
    // Later, we could possibly change starting progress to keep integrity of points gap between triangles.
    
    // For AB edge
    float xProgress = 0.f;
    // For AC edge
    float yProgress = 0.f;

    /* Loop breakers */

    auto continueX = [&]() -> bool { return xProgress < lAB; };
    auto continueY = [&]() -> bool
    {
        return yProgress < lAC * (lAB - xProgress) / lAB;
    };

    for(xProgress = 0.f; continueX(); xProgress += m_PointGap)
    {
        for(yProgress = 0.f; continueY(); yProgress += m_PointGap)
        {
            glm::vec3 range = {std::abs(m_MaxDisturb.x - m_MinDisturb.x), std::abs(m_MaxDisturb.y - m_MinDisturb.y), std::abs(m_MaxDisturb.z - m_MinDisturb.z)};
            
            const glm::vec3 randomness
            {
                (range.x != 0.f ? std::fmod((float)m_RandomGenerator(), range.x) : 0.f) + m_MinDisturb.x,
                (range.y != 0.f ? std::fmod((float)m_RandomGenerator(), range.y) : 0.f) + m_MinDisturb.y,
                (range.z != 0.f ? std::fmod((float)m_RandomGenerator(), range.z) : 0.f) + m_MinDisturb.z
            };

            glm::vec3 position = A + (xProgress + randomness.x) * x + (yProgress + randomness.y) * y + randomness.z * n;
                //+ randomness.z * n; // n is the local z axis (outside of triangle plane)

            output.addPoint(PointCloud::Element(position, n));
        }
    }
}

void PointCloudProcessor::setDensity(float d)
{
    m_PointGap = 1.f / d;
}

void PointCloudProcessor::setMinDisturb(const glm::vec3& d)
{
    m_MinDisturb = d;
}

void PointCloudProcessor::setMaxDisturb(const glm::vec3& d)
{
    m_MaxDisturb = d;
}

void PointCloudProcessor::setSeed(uint32_t seed)
{
    m_RandomGenerator.seed(seed);
}


float PointCloudProcessor::getDensity() const
{
    return 1.f / m_PointGap;
}

const glm::vec3& PointCloudProcessor::getMinDisturb() const
{
    return m_MinDisturb;
}

const glm::vec3& PointCloudProcessor::getMaxDistrub() const
{
    return m_MaxDisturb;
}

