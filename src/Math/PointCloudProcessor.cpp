#include "Math/PointCloudProcessor.h"

PointCloud PointCloudProcessor::process(const Mesh& mesh) const
{
    PointCloud out;
    out.reservePoints(mesh.getVerticesCount());

    for(size_t i = 0; i < mesh.getVerticesCount(); i++)
    {
        PointCloud::Element element;
        element.position = mesh.getVertices()[i].position;
        element.normal = mesh.getVertices()[i].normal;

        out.addPoint(element);
    }

    return out;
}

void PointCloudProcessor::setDensity(size_t d)
{
    m_PointsPerEdge = d;
}

void PointCloudProcessor::setMinDisturb(const glm::vec3& d)
{
    m_MinDisturb = d;
}

void PointCloudProcessor::setMaxDisturb(const glm::vec3& d)
{
    m_MaxDisturb = d;
}
