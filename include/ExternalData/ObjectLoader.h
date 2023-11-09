#pragma once

#include <string>

#include "Data/Mesh.h"
#include "Data/PointCloud.h"

class ObjectLoader
{
public:

    /**
     * @brief Loads a mesh from its file path. Extensions allowed are .obj and .ply.
     * @throws @ref FileNotLoaded if path is not valid / error occured while loading / file extension is unsupported / mesh couldn't be loaded.
     * 
     * @param filePath Path of the mesh file.
     * @return Mesh An instance of a mesh freshly created.
     */
    static Mesh LoadMesh(const std::string& filePath);

    /**
     * @brief Loads a mesh directly from file explorer. This function will open a file explorer window and asks user to select
     * @throws @ref FileNotLoaded if mesh couldn't be loaded.
     * @todo Still not implemented.
     * 
     * @return Mesh 
     */
    static Mesh LoadMesh();

    /**
     * @brief Loads a file as raw text.
     * @throws @ref FileNotLoaded If path is not valid / error occured while loading.
     * 
     * @return std::string Raw text of file.
     */
    static std::string LoadTextFile(const std::string& filePath);

private:
    static std::string GetAbsolutePath(const std::string& relativePath, bool addQuotes = true);

private:
    static Mesh LoadOBJMesh(const std::string& filePath);
    static Mesh LoadPLYMesh(const std::string& filePath);
};