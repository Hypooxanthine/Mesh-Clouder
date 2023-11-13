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

    void setGridSize(const glm::vec2& size);
    void setGridUnits(const glm::vec2& units);

private:
    glm::vec2 m_GridSize;
    glm::vec2 m_GridUnits;
};