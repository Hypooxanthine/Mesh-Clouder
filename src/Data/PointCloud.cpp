#include "Data/PointCloud.h"

PointCloud::PointCloud()
{}

PointCloud::PointCloud(const PointCloud& other)
    : m_PointsPositions(other.m_PointsPositions)
{}

PointCloud::PointCloud(PointCloud&& other)
    : m_PointsPositions(std::move(other.m_PointsPositions))
{}

PointCloud& PointCloud::operator=(const PointCloud& other)
{
    m_PointsPositions = other.m_PointsPositions;
    return *this;
}

PointCloud& PointCloud::operator=(PointCloud&& other)
{
    m_PointsPositions = other.m_PointsPositions;
    return *this;
}

void PointCloud::reservePoints(size_t count)
{
    m_PointsPositions.reserve(count);
}

const std::vector<PointCloud::Element>& PointCloud::getPointsData() const
{
    return m_PointsPositions;
}

const PointCloud::Element* PointCloud::getRawPointsData() const
{
    return m_PointsPositions.data();
}

void PointCloud::addPoint(const PointCloud::Element& element)
{
    m_PointsPositions.push_back(element);
}
