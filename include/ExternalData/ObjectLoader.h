#pragma once

#include <string>
#include <vector>

#include "Data/Mesh.h"
#include "Data/PointCloud.h"
#include "Data/Project.h"

/**
 * @brief Deals with data loading.
 * 
 */
class ObjectLoader
{
public:

    static Project LoadProject(const std::string& filePath);
    static Project LoadProject();

    static void SaveProject(const Project& p);
    static void SaveProjectAs(Project& p);

    /**
     * @brief Loads a mesh from its file path. Extensions allowed are .obj and .ply.
     * @throws @ref FileNotLoaded if path is not valid / error occured while loading / file extension is unsupported / mesh couldn't be loaded.
     * 
     * @param filePath Path of the mesh file.
     * @return Mesh An instance of a mesh freshly created.
     */
    static Mesh LoadMesh(const std::string& filePath);

    /**
     * @brief Loads a mesh directly from file explorer. This function will open a file explorer window and asks user to select the mesh to load.
     * @throws @ref FileNotLoaded if mesh couldn't be loaded.
     * @todo Still not implemented.
     * 
     * @return Mesh 
     */
    static Mesh LoadMesh();

    /**
     * @brief Saves a point cloud in a new file.
     * 
     * @param data The point cloud to save.
     * @param filePath Where to save the file (path + file name).
     * @param binary If true, saves in binary format. If false, saves in ASCII format.
     */
    static void SavePointCloud(const PointCloud& data, const std::string& filePath, bool binary = true);
    
    /**
     * @brief Saves a point cloud in a new file. This function will open a file explorer window and asks user to select a path to save the point cloud.
     * 
     * @param data The point cloud to save.
     */
    static void SavePointCloud(const PointCloud& data);

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

private:
    static std::vector<std::string> s_ProjectExt;
    static std::vector<std::string> s_MeshesExts;
};