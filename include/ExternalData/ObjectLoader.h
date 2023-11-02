#pragma once

#include <string>

#include "Data/Mesh.h"
#include "Data/PointCloud.h"

class ObjectLoader
{
public:

    /**
     * @brief Loads a mesh from its file path. Extensions allowed are .obj and .ply.
     * @throws \ref FileNotLoaded.
     * 
     * @param filePath Path of the mesh file.
     * @return Mesh An instance of a mesh freshly created.
     */
    static Mesh LoadMesh(const std::string& filePath);

    /**
     * @brief Loads a mesh directly from file explorer. This function will open a file explorer window and asks user to select
     * @throws \ref FileNotLoaded.
     * @todo Still not implemented.
     * 
     * @return Mesh 
     */
    static Mesh LoadMesh();

private:
    static Mesh LoadOBJMesh(const std::string& filePath);
    static Mesh LoadPLYMesh(const std::string& filePath);
};