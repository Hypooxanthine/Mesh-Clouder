#pragma once

#include "RenderObject.h"

#include "Data/PointCloud.h"
#include "Data/Mesh.h"

class RenderPointCloud : public RenderObject
{
public:
    RenderPointCloud();
    RenderPointCloud(const RenderPointCloud& other) = delete;
    RenderPointCloud(RenderPointCloud&& other) = delete;
    ~RenderPointCloud();

    RenderPointCloud& operator=(const RenderPointCloud& other) = delete;
    RenderPointCloud& operator=(RenderPointCloud&& other) = delete;

    virtual void render(const Renderer& renderer, const Camera& camera) const override;

    void setPointCloud(const PointCloud& pc);
    void setPointCloud(PointCloud&& pc);

    float getCircleRadius() const;
    void setCircleRadius(float r);

private:
    void init();

private:
    /* Data */
    PointCloud m_PointCloudData;

    /* OpenGL objects */
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<VertexBufferLayout> m_Layout;

    /* Settings */
    float m_CircleRadius = 1.f;
};
