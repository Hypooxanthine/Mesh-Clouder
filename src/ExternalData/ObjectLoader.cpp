#include "ExternalData/ObjectLoader.h"

#include <happly/happly.h>
#include <OBJ_Loader/OBJ_Loader.h>

#include "ExternalData/FileExplorer.h"
#include "Exceptions/FileNotLoaded.h"

Mesh ObjectLoader::LoadMesh(const std::string& filePath)
{
    if (filePath.ends_with(".obj"))
        return LoadOBJMesh(filePath);
    else if (filePath.ends_with(".ply"))
        return LoadPLYMesh(filePath);

    std::cout << filePath << std::endl;
    
    throw FileNotLoaded("Unsupported file extension for \"" + filePath + "\".");
}

Mesh ObjectLoader::LoadMesh()
{
    std::string path = FileExplorer::GetFileFromFileExplorer();

    if (path.empty()) throw FileNotLoaded("Empty path.");

    return LoadMesh(path);
}

Mesh ObjectLoader::LoadOBJMesh(const std::string& filePath)
{
    objl::Loader l;

    if (!l.LoadFile(filePath))
        throw FileNotLoaded("OBJ_Loader couldn't load file.");
    
    Mesh mesh;

    for (size_t m = 0 ; m < l.LoadedMeshes.size() ; m++)
    {
        for (size_t v = 0 ; v < l.LoadedVertices.size() ; v++)
        {
            Vector3f pos;
            pos.x = l.LoadedVertices[v].Position.X;
            pos.y = l.LoadedVertices[v].Position.Y;
            pos.z = l.LoadedVertices[v].Position.Z;

            Vector3f normal;
            normal.x = l.LoadedVertices[v].Normal.X;
            normal.y = l.LoadedVertices[v].Normal.Y;
            normal.z = l.LoadedVertices[v].Normal.Z;

            Vector2f texCoords;
            texCoords.x = l.LoadedVertices[v].TextureCoordinate.X;
            texCoords.y = l.LoadedVertices[v].TextureCoordinate.Y;

            mesh.addVertex(Vertex(pos, normal, texCoords));
        }

        for (size_t i = 0 ; i < l.LoadedIndices.size() ; i += 3)
        {
            mesh.defineTriangle
            (
                l.LoadedIndices[i], l.LoadedIndices[i + 1], l.LoadedIndices[i + 2]
            );
        }
    }

    return mesh;
}

Mesh ObjectLoader::LoadPLYMesh(const std::string& filePath)
{
    throw FileNotLoaded(".ply files are not supported yet.");
}
