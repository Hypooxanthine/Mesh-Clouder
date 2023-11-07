#pragma once

#include <vector>
#include <cstdint>

#include "Vertex.h"

/**
 * @brief The Mesh class represents a mesh in memory. It contains its vertices and indices.
 * 
 */
class Mesh
{
public:
    Mesh() = default;
    ~Mesh() = default;
    Mesh(const Mesh& other);
    Mesh(Mesh&& other);
    Mesh& operator=(const Mesh& other);
    Mesh& operator=(Mesh&& other);

    /**
     * @brief Reserves memory space for vertices. Avoid multiple memory extension of vertices vector.
     * 
     * @param nb The number of vertices to reserve.
     */
    void reserveVertices(unsigned int nb);

    /**
     * @brief Reserves memory space for indices. Avoid multiple memory extension of vertices vector.
     * 
     * @param nb The number of indices to reserve. Must be multiple of 3.
     */
    void reserveIndices(unsigned int nb);

    /**
     * @brief Clears vertices and indices.
     * 
     */
    void clear();

    /**
     * @brief Adds a vertex to the mesh.
     * 
     * @param v A const reference to the vertex to add.
     */
    void addVertex(const Vertex& v);

    /**
     * @brief Adds a vertex to the mesh.
     * 
     * @param v An rvalue reference to the vertex to add.
     */
    void addVertex(Vertex&& v);

    /**
     * @brief Defines a triangle defined by 3 vertices, designated by their indices.
     * 
     * @param a Index of the first vertex.
     * @param b Index of the second vertex.
     * @param c Index of the third vertex.
     */
    void defineTriangle(unsigned int a, unsigned int b, unsigned int c);

    /**
     * @brief Get the number of vertices stored in this mesh.
     * 
     * @return size_t The number of vertices.
     */
    size_t getVerticesCount() const;

    /**
     * @brief Get the number of indices stored in this mesh.
     * 
     * @return size_t The number of indices. It is a multiple of 3.
     */
    size_t getIndicesCount() const;

    /**
     * @brief Get the number of triangles defined in this mesh.
     * 
     * @return size_t The number of triangles. This value is \ref getIndicesCount / 3.
     */
    size_t getTrianglesCount() const;

    /**
     * @brief Get the raw vertices data (for example, to give to OpenGL).
     * 
     * @return const Vertex* Raw vertices data.
     */
    const Vertex* getRawVerticesData() const;

    /**
     * @brief Get the rax indices data (for example, to give to OpenGL).
     * 
     * @return const unsigned* Raw indices data.
     */
    const unsigned int* getRawIndicesData() const;

private:
    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
};