#include "Rendering/Objects/RenderGrid.h"

#include "Rendering/Objects/MeshGenerator.h"

RenderGrid::RenderGrid()
    : RenderGrid({10.f, 10.}, {1.f, 1.f})
{
}

RenderGrid::RenderGrid(const glm::vec2& size, const glm::vec2& units)
    : RenderMesh()
{
    setMesh(MeshGenerator::GenQuad());
    m_Shader = std::make_unique<Shader>();
    m_Shader->loadFromFile("Resources/coordsVert.glsl", "Resources/coordsFrag.glsl");

    setGridSize(size);
    setGridUnits(units);
}

RenderGrid::~RenderGrid()
{

}

const glm::vec2& RenderGrid::getGridSize() const
{
    return m_GridSize;
}

const glm::vec2& RenderGrid::getGridUnits() const
{
    return m_GridUnits;
}

void RenderGrid::setGridSize(const glm::vec2& size)
{
    m_GridSize = size;
    setScale(glm::vec3(size.x, 1.f, size.y));
    setTranslation(glm::vec3(-size.x / 2.f, 0.f, -size.y / 2.f));
}

void RenderGrid::setGridUnits(const glm::vec2& units)
{
    m_GridUnits = units;
}
