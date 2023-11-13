#pragma once

#include "RenderMesh.h"

class RenderGrid : public RenderMesh
{
public:
    RenderGrid();
    RenderGrid(const glm::vec2& size, const glm::vec2& units);
    ~RenderGrid();

    const glm::vec2& getGridSize() const;
    const glm::vec2& getGridUnits() const;

    /**
     * @brief Set the grid size and centers its origin to (0,0).
     * 
     * @param size x and y dimensions of the grid.
     */
    void setGridSize(const glm::vec2& size);

    /**
     * @brief Set the Grid units. For example, for (1.f, 1.f), grid lines will be spaces by 1.f on X and 1.f on Y.
     * @todo Does nothing yet, a uniforms system is required.
     * 
     * @param units x and y units.
     */
    void setGridUnits(const glm::vec2& units);

private:
    glm::vec2 m_GridSize;
    glm::vec2 m_GridUnits;
};