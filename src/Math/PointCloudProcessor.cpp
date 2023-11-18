#include "Math/PointCloudProcessor.h"

#include "Math/Math.h"

PointCloud PointCloudProcessor::process(const Mesh& mesh) const
{
    PointCloud out;
    /*
    // Initialize data size
    unsigned int samples = 1;
    unsigned int power = 1;
    for(unsigned int i = 1; i < samples; i++) power *= 6;
    size_t numberOfPoints = (power - 1) / 5; 
    out.reservePoints(numberOfPoints);

    for(size_t i = 0; i < mesh.getIndicesCount(); i += 3)
    {
        const auto& iA = mesh.getIndices()[i + 0];
        const auto& iB = mesh.getIndices()[i + 1];
        const auto& iC = mesh.getIndices()[i + 2];
        const glm::vec3& A = mesh.getVertices()[iA].position;
        const glm::vec3& B = mesh.getVertices()[iB].position;
        const glm::vec3& C = mesh.getVertices()[iC].position;

        Math::SampleTriangleRecursive(A, B, C, out, samples);
    }

    */

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
            output.addPoint(PointCloud::Element(A + xProgress * x + yProgress * y, n));
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
