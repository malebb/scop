#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

namespace SCOP
{
    struct Vertex
    {
        float x{0.f};
        float y{0.f};
        float z{0.f};
    };

    struct Face
    {
        Vertex v;
        Vertex vt;
        Vertex vn;
    };

    enum VertexType: uint8_t
    {
        position,
        texture,
        normal
    };

	class ObjParser
	{
        public:

            ObjParser();
            ObjParser(const std::string& t_objPath);

            // print functions
            void printParsedFile(void) const;
            void printVertex(const Vertex& t_vertex) const;

        private:
            void parseFaces(std::istringstream& t_ss);
            void parseFile(std::ifstream& t_objFile);
            void parseLine(const std::string& t_line);
            void parseVertexData(VertexType t_vertexType, std::istringstream& t_ss);
            std::vector<Vertex> m_posVertex;
            std::vector<Vertex> m_normVertex;
            std::vector<Vertex> m_textVertex;
            std::vector<Face> m_faces;
            std::string m_mtllibPath;
            std::string m_objName;
            std::string m_usemtl;
	};
};
