#pragma once

#include <cstddef>

namespace Math
{

// vector

struct vec3
{
    vec3() : x(0), y(0), z(0)
    {

    }

    vec3(float t_x, float t_y, float t_z)
    : x(t_x), y(t_y), z(t_z)
    {

    }

    float x;
    float y;
    float z;
    
    static constexpr std::size_t size = 3;
};

struct vec2
{

    vec2() : x(0), y(0)
    {

    }
    
    vec2(float t_x, float t_y)
    : x(t_x), y(t_y)
    {

    }

    float x;
    float y;

    static constexpr std::size_t size = 2;
};

// matrix

struct mat4
{
    mat4(float t_value)
    {
        for (unsigned int i = 0; i < size; ++i)
        {
            data[i][i] = t_value;
        }
    }

    static constexpr std::size_t size = 4;
    float data[size][size]{{0}};
};

inline struct mat4 scale(struct mat4 t_mat, vec3 t_vec)
{
    float* vecValues = reinterpret_cast<float*>(&t_vec);

    for (unsigned int i = 0; i < 3; ++i)
    {
        t_mat.data[i][i] *= vecValues[i];
    }
    return t_mat;
}

}