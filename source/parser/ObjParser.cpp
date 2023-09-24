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
        Vertex vertexData;
        t_ss >> vertexData.x;
        t_ss >> vertexData.y;
        t_ss >> vertexData.z;
        switch (t_vertexType)
        {
            case VertexType::position:
                m_posVertex.push_back(vertexData);
                break;
            case VertexType::texture:
                m_textVertex.push_back(vertexData);
                break;
            case VertexType::normal:
                m_normVertex.push_back(vertexData);
                break;
        }
}

void ObjParser::parseFaces(std::istringstream& t_ss)
{
    std::string buf;
    while (t_ss.rdbuf()->in_avail())
    {
        t_ss >> buf;
        size_t v, vt, vn;
        sscanf(buf.data(),"%ld/%ld/%ld", &v, &vt, &vn);
        if (v <= 0  || v > m_posVertex.size() || vt > m_textVertex.size()
                || vn > m_normVertex.size())
        {
            throw("Error: unknown vertex index");
        }
        m_faces.push_back({m_posVertex.at(v - 1),
                m_textVertex.at(vt - 1),
                m_normVertex.at(vn - 1)});
    }
}

void ObjParser::printParsedFile(void) const
{
    std::cout << "mrllib: " << m_mtllibPath << std::endl;
    std::cout << "o: " << m_objName << std::endl;
    for (std::vector<Vertex>::const_iterator it = m_posVertex.begin(); it != m_posVertex.end(); ++it)
    {
        std::cout << "v: ";
        printVertex(*it);
    }
    for (std::vector<Vertex>::const_iterator it = m_textVertex.begin(); it != m_textVertex.end(); ++it)
    {
        std::cout << "vt: ";
        printVertex(*it);
    }
    for (std::vector<Vertex>::const_iterator it = m_normVertex.begin(); it != m_normVertex.end(); ++it)
    {
        std::cout << "vn: ";
        printVertex(*it);
    }
    std::cout << "usemtl: " << m_usemtl << std::endl;
}

void ObjParser::printVertex(const Vertex& t_vertex) const
{
    std::cout << t_vertex.x << "," << t_vertex.y << "," << t_vertex.z << std::endl;
}
