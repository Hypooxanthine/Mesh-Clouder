#include "Data/PointCloud.h"

PointCloud::PointCloud()
{}

PointCloud::PointCloud(const PointCloud& other)
    : m_PointsPositions(other.m_PointsPositions), m_Indices(other.m_Indices)
{}

PointCloud::PointCloud(PointCloud&& other)
    : m_PointsPositions(std::move(other.m_PointsPositions)), m_Indices(std::move(other.m_Indices))
{}

PointCloud& PointCloud::operator=(const PointCloud& other)
{
    m_PointsPositions = other.m_PointsPositions;
    m_Indices = other.m_Indices;
    return *this;
}

PointCloud& PointCloud::operator=(PointCloud&& other)
{
    m_PointsPositions = std::move(other.m_PointsPositions);
    m_Indices = std::move(other.m_Indices);
    return *this;
}

void PointCloud::reservePoints(size_t count)
{
    m_PointsPositions.reserve(count);
    m_Indices.reserve(count);
}

void PointCloud::clear()
{
    m_Indices.clear();
    m_PointsPositions.clear();
}

size_t PointCloud::getPointsCount() const
{
    return m_PointsPositions.size();
}

const std::vector<PointCloud::Element>& PointCloud::getPointsData() const
{
    return m_PointsPositions;
}

const PointCloud::Element* PointCloud::getRawPointsData() const
{
    return m_PointsPositions.data();
}

size_t PointCloud::getIndicesCount() const
{
    return m_Indices.size();
}

const std::vector<unsigned int>& PointCloud::getIndicesData() const
{
    return m_Indices;
}

const unsigned int* PointCloud::getRawIndicesData() const
{
    return m_Indices.data();
}

void PointCloud::addPoint(const PointCloud::Element& element)
{
    m_PointsPositions.push_back(element);
    m_Indices.push_back(m_PointsPositions.size() - 1);
}
