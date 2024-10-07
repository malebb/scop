#include "ObjParser.h"

#include <sstream>
#include <cstdio>

using SCOP::ObjParser;

ObjParser::ObjParser()
{

}

ObjParser::ObjParser(const std::string& t_objPath)
{
    constexpr std::string_view objExt = ".obj";
    if (t_objPath.substr(t_objPath.size() - objExt.size()).compare(".obj"))
    {
        throw(std::invalid_argument("Error: Wrong file extension ==> only .obj"));
    }
    std::ifstream objFile;

    objFile.open(t_objPath, std::ifstream::in);
    if (!objFile.is_open())
    {
        throw(std::invalid_argument("Error: The .obj file could not be found"));
    }
    parseFile(objFile);
}

void ObjParser::parseFile(std::ifstream& t_objFile)
{
    std::string line;
    while (std::getline(t_objFile, line))
    {
        parseLine(line);
    }
}

void ObjParser::parseLine(const std::string& t_line)
{
    std::istringstream ss(t_line);
    std::string dataType;

    ss >> dataType;
   
    if (!dataType.compare("mtllib"))
    {
        ss >> m_mtllibPath;
    }
    else if (!dataType.compare("usemtl"))
    {
        ss >> m_usemtl;
    }
    else if (!dataType.compare("o"))
    {
        ss >> m_objName;
    }
    else if (!dataType.compare("v"))
    {
        parseVertexData(VertexType::position, ss);
    }
    else if (!dataType.compare("vt"))
    {
        parseVertexData(VertexType::texture, ss);
    }
    else if (!dataType.compare("vn"))
    {
        parseVertexData(VertexType::normal, ss);
    }
    else if (!dataType.compare("f"))
    {
        parseFaces(ss);
    }
}

void ObjParser::parseVertexData(VertexType t_vertexType, std::istringstream& t_ss)
{
        Math::vec3 pos;
        Math::vec2 texCoord;
        Math::vec3 normal;

        switch (t_vertexType)
        {
            case VertexType::position:
                    t_ss >> pos.x;
                    t_ss >> pos.y;
                    t_ss >> pos.z;
                    m_positions.push_back(pos);
                break;
            case VertexType::texture:
                    t_ss >> texCoord.x;
                    t_ss >> texCoord.y;
                    m_textCoords.push_back(texCoord);
                break;
            case VertexType::normal:
                    t_ss >> normal.x;
                    t_ss >> normal.y;
                    t_ss >> normal.z;
                    m_normals.push_back(normal);
                break;
        }
}

void ObjParser::parseFaces(std::istringstream& t_ss)
{
    std::string buf;
    while (t_ss.rdbuf()->in_avail())
    {
        t_ss >> buf;
        size_t v = 0;
        size_t vt = 0;
        size_t vn = 0;
        sscanf(buf.data(),"%ld/%ld/%ld", &v, &vt, &vn);
        if (v > m_positions.size() || vt > m_textCoords.size()
                || vn > m_normals.size())
        {
            throw(std::invalid_argument("Error: unknown vertex index"));
        }

        Vertex vertex;
        static unsigned int indice = 0;
        vertex.v = m_positions.at(v - 1);
        if (vt)
            vertex.vt = m_textCoords.at(vt - 1);
        if (vn)
            vertex.vn = m_normals.at(vn - 1);

        m_vertices.push_back(vertex);
        m_indices.push_back(indice);
        indice++;
    }
}

const std::vector<SCOP::Vertex>& ObjParser::getVertices(void) const
{
    return m_vertices;
}

const std::vector<unsigned int>& ObjParser::getIndices(void) const
{
    return m_indices;
}