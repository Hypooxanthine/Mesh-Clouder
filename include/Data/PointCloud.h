#pragma once

#include <vector>

#include "Vector.h"

/**
 * @brief Storage class for point clouds.
 * 
 */
class PointCloud
{
public:
    /**
     * @brief A point in a point cloud is represented by this data structure.
     * 
     */
    struct Element
    {
        Vector3f position;
        Vector3f normal;
    };
public:
    PointCloud();
    PointCloud(const PointCloud& other);
    PointCloud(PointCloud&& other);
    PointCloud& operator=(const PointCloud& other);
    PointCloud& operator=(PointCloud&& other);

    void reservePoints(size_t count);

    size_t getPointsCount() const;
    const std::vector<Element>& getPointsData() const;
    const Element* getRawPointsData() const;
    size_t getIndicesCount() const;
    const std::vector<unsigned int>& getIndicesData() const;
    const unsigned int* getRawIndicesData() const;

    void addPoint(const Element& element);

private:
    std::vector<Element> m_PointsPositions;
    std::vector<unsigned int> m_Indices;
};