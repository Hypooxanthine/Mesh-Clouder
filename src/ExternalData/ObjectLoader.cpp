#include "ExternalData/ObjectLoader.h"

#include <fstream>
#include <filesystem>
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

    return mesh;
}

Mesh ObjectLoader::LoadPLYMesh(const std::string& filePath)
{
    try
    {
        happly::PLYData plyIn(filePath);
        Mesh out;
        
        auto xPos = plyIn.getElement("vertex").getProperty<float>("x");
        auto yPos = plyIn.getElement("vertex").getProperty<float>("y");
        auto zPos = plyIn.getElement("vertex").getProperty<float>("z");
        auto xn = plyIn.getElement("vertex").getProperty<float>("nx");
        auto yn = plyIn.getElement("vertex").getProperty<float>("ny");
        auto zn = plyIn.getElement("vertex").getProperty<float>("nz");
        

        std::vector<float> u, v;
        bool hasUV = true;

        try
        {
            u = plyIn.getElement("vertex").getProperty<float>("s");
            v = plyIn.getElement("vertex").getProperty<float>("t");
        }
        catch(const std::exception& e)
        {
            hasUV = false;
        }
        
        out.reserveVertices(xPos.size());

        for (size_t i = 0; i < xPos.size(); i++)
        {
            Vertex vertex;

            vertex.position = {xPos[i], yPos[i], zPos[i]};
            vertex.normal = {xn[i], yn[i], zn[i]};
            vertex.texCoords = (hasUV ? Vector2f{u[i], v[i]} : Vector2f{0.f, 0.f});

            std::cout << "Vertex added, pos: (" << vertex.position.x << ", " << vertex.position.y << ", " << vertex.position.z << ")\n";

            out.addVertex(std::move(vertex));
        }

        try
        {
            auto indices = plyIn.getElement("face").getListProperty<unsigned int>("vertex_indices");
            for (size_t i = 0; i < indices.size(); i++)
                out.defineTriangle(indices[i][0], indices[i][1], indices[i][2]); // Does not throw anything so once we loaded vertices, we're sure no exception will be thrown, so we wont be defining triangles twice.
        }
        catch(const std::exception& e)
        {
            try
            {
                auto indices = plyIn.getElement("face").getListProperty<int>("vertex_indices");
                for (size_t i = 0; i < indices.size(); i++)
                    out.defineTriangle((unsigned int)indices[i][0], (unsigned int)indices[i][1], (unsigned int)indices[i][2]);
            }
            catch(const std::exception& e)
            {
                // We don't throw anything but we need to print that it is weird to load a mesh without face element or vertices property.
                std::cerr << e.what() << '\n';
            }
            
        }

        return out;
    }
    catch(const std::exception& e)
    {
        throw FileNotLoaded(std::string("happly couldn't load file: ") + e.what());
    }
}

std::string ObjectLoader::LoadTextFile(const std::string& filePath)
{
    std::ifstream ifs;

    ifs.open(filePath);
        if (!ifs.is_open())
            throw FileNotLoaded("Couldn't load " + GetAbsolutePath(filePath) + ".");

        std::string rawText;
        std::string line;
        while (!ifs.eof())
        {
            std::getline(ifs, line);
            rawText += line;
            rawText += "\n";
        }
    ifs.close();

    return rawText;
}

std::string ObjectLoader::GetAbsolutePath(const std::string& relativePath, bool addQuotes)
{
    std::string out =  std::filesystem::current_path().string() + "\\" + relativePath;

    if (addQuotes) out = "\"" + out + "\"";

    return out;
}