#include "Rendering/Objects/MeshGenerator.h"

Mesh MeshGenerator::GenCircle(unsigned int samples)
{
    // At least 3 samples...
    if(samples < 3) samples = 3;

    Mesh m;
    m.reserveVertices(samples + 1);
    m.reserveTriangles(samples);

    // Pointing upwards
    const Vector3f normal{ 0.f, 1.f, 0.f };

    m.addVertex(Vertex({ 0.f, 0.f, 0.f }, normal, { 0.5f, 0.5f }));
    m.addVertex(Vertex({ 1.f, 0.f, 0.f }, normal, { 1.0f, 0.5f }));

    for(unsigned int i = 1; i < samples; i++)
    {
        // Creating vertex of index i + 1
        const float angle = glm::radians((float)i * 360.f / (float)samples);

        m.addVertex(
        {
            { glm::cos(angle), 0.f, glm::sin(angle) },
            normal,
            { glm::cos(angle) / 2.f + 0.5f, glm::sin(angle) / 2.f + 0.5f }
        });

        m.defineTriangle(0, i, i + 1);
    }

    m.defineTriangle(0, samples, 1); // Last triangle

    return m;
}

Mesh MeshGenerator::GenQuad()
{
    Mesh m;

    m.reserveVertices(4);
    m.reserveTriangles(2);

    const Vector3f normal = { 0.f, 1.f, 0.f };

    // Order :
    // A B
    // D C
    m.addVertex(Vertex{{0.f, 0.f, 0.f}, normal, {0.f, 1.f}});
    m.addVertex(Vertex{{1.f, 0.f, 0.f}, normal, {1.f, 1.f}});
    m.addVertex(Vertex{{0.f, 0.f, 1.f}, normal, {1.f, 0.f}});
    m.addVertex(Vertex{{1.f, 0.f, 1.f}, normal, {0.f, 0.f}});

    m.defineTriangle(2, 3, 1);
    m.defineTriangle(2, 1, 0);

    return m;
}