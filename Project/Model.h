#pragma once
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>

#include "Camera.h"
#include "Sphere.h"
#include "Triangle.h"

using vertices_t = std::vector<glm::vec3>;
using clr = SDL_Color;

class Model : virtual public SceneObject
{
public:
    vertices_t m_vertices;
    vector<Triangle> tris;
    clr m_color{255,255,255,255};
    glm::vec3 offset{0,0,0};

    Model(const std::shared_ptr<Material>& material, const glm::vec3 off) : SceneObject(material)
    {
        offset = off;
    }

    void SetColor(const clr color)
    {
        m_color = color;
    }
    
    void Draw(FrameBuffer& fb, glm::mat4& model, Camera& camera)
    {
        for (int i = 0; i < m_vertices.size()-2; ++i)
        {
            glm::vec4 p1 = model * glm::vec4{ m_vertices[i + 0], 1};
            glm::vec4 p2 = model * glm::vec4{ m_vertices[i + 1], 1};
            glm::vec4 p3 = model * glm::vec4{ m_vertices[i + 2], 1};

            p1 = camera.ModelToView(p1);
            p2 = camera.ModelToView(p2);
            p3 = camera.ModelToView(p3);

            glm::ivec2 s1 = camera.ViewToScreen(p1);
            glm::ivec2 s2 = camera.ViewToScreen(p2);
            glm::ivec2 s3 = camera.ViewToScreen(p3);

            fb.DrawTriangle(s1.x,s1.y,s2.x,s2.y,s3.x,s3.y, m_color);
        }
    }
    
    bool Load(const std::string& filename)
    {
        // open file using ifstream (input file stream)
        std::ifstream stream(filename);
        // check if stream is_open
        if (!stream.is_open())
        {
            std::cerr << "Stream is not open!";
            return false;
        }

        vertices_t vertices;
        std::string line;
        while (std::getline(stream, line))
        {
            // read in vertex positions
            // https://cplusplus.com/reference/string/string/substr/
            if (line.substr(0,2) == "v ")
            {
                // read position of vertex
                std::istringstream sstream{ line.substr(2) };
                glm::vec3 position;
                sstream >> position.x;
                sstream >> position.y;
                sstream >> position.z;
                //position += offset;

                vertices.push_back(position);
            }
            // read in faces (triangles)
            else if (line.substr(0,2) == "f ")
            {
                // read face (triangle), index of vertex position in vertices array [1, 2, 3]
                std::istringstream sstream{ line.substr(2) };
                std::string str;
                // https://en.cppreference.com/w/cpp/string/basic_string/getline
                while (std::getline(sstream, str, ' '))
                {
                    std::istringstream sstream(str);
                    std::string indexString;

                    // read each triangle index (position, normal, uv)
                    size_t i = 0;
                    unsigned int index[3] = { 0, 0, 0 }; // 0 = position, 1 = normal, 2 = uv
                    while (std::getline(sstream, indexString, '/'))
                    {
                        if (!indexString.empty())
                        {
                            std::istringstream indexStream{ indexString };
                            indexStream >> index[i];
                        }
                        i++;
                    }

                    // check if index 0 (position) is valid
                    if (index[0] != 0)
                    {
                        // get vertex at index position
                        // index is 1 based, need to subtract one for array
                        glm::vec3 position = vertices[index[0]-1];

                        m_vertices.push_back(position);
                    }
                }
            }
        }

        stream.close();
        std::cout << "Model successfully loaded: " << filename << '\n';

        /*
        for (auto position : m_vertices)
        {
            cout << position[0] << ", " << position[1] << ", " << position[2] << "\n";
        }
        */
        AssembleTris();
        
        return true;
    }

    void AssembleTris()
    {
        tris.clear();
        for (int i = 0; i < m_vertices.size(); i+=3 )
        {
            tris.emplace_back(m_vertices[i]+offset,m_vertices[i+1]+offset,m_vertices[i+2]+offset,m_material);
        }
        m_t = 5;
        /*
        for (const auto tri : tris)
        {
            m_t += tri.m_z;
        }
        m_t /= tris.size();
        */
        /*
        int j = tris.size();
        for (int k = 0; k < j; k++)
        {
            for (int i = 0; i < j; i++)
            {
                if (tris.at(k) == tris.at(i))
                {
                    tris.erase(tris.begin()+i);
                    j--;
                }
            }
        }
        */
    }

    static bool ZSort(Triangle& i1, Triangle& i2)
    {
        //cout << i1.m_t << ", " << i2.m_t << '\n';
        return (i1.m_z < i2.m_z);
    }

    bool Hit(Ray& ray, RaycastHit& rayhit) override
    {
        auto s = new Sphere(offset, 1, nullptr);
        if (!s->Hit(ray, rayhit))
        {
            return false;
        }
        sort(tris.begin(), tris.end(),ZSort);
        // check cast ray with mesh triangles 
        for (auto& tri : tris)
        {
            if (tri.Hit(ray,rayhit))
            {
                return true;
            }
        }
        return false;
    }
};
