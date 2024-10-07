#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "Math.h"

namespace SCOP
{
    struct Vertex
    {
        Math::vec3 v;
        Math::vec2 vt;
        Math::vec3 vn;
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
            
            [[nodiscard]] std::vector<Vertex>& getVertices(void);
            [[nodiscard]] std::vector<unsigned int>& getIndices(void);

        private:
            void parseFaces(std::istringstream& t_ss);
            void parseFile(std::ifstream& t_objFile);
            void parseLine(const std::string& t_line);
            void parseVertexData(VertexType t_vertexType, std::istringstream& t_ss);

            std::vector<Vertex> m_vertices;
            std::vector<unsigned int> m_indices;
            std::vector<Math::vec3> m_positions;
            std::vector<Math::vec2> m_textCoords;
            std::vector<Math::vec3> m_normals;
            std::string m_mtllibPath;
            std::string m_objName;
            std::string m_usemtl;
	};
};
