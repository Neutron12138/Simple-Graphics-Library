#ifndef MESH_GENERATOR_HPP
#define MESH_GENERATOR_HPP

#include "mesh.hpp"
#include "../system/math.hpp"

namespace sgl
{
    class MeshGenerator
    {
    public:
        struct Sphere
        {
            glm::vec3 half = glm::vec3(1.0f);
            glm::uvec2 subdivision = glm::uvec2(36, 18);

            Sphere() {}
            Sphere(const glm::vec3 &hf, const glm::uvec2 &su = glm::uvec2(36, 18))
                : half(hf), subdivision(su) {}
            Sphere(Float32 radius, const glm::uvec2 &su = glm::uvec2(36, 18))
                : half(glm::vec3(radius)), subdivision(su) {}
        };

        struct Box
        {
            glm::vec3 half = glm::vec3(1.0f);
            glm::uvec3 subdivision = glm::uvec3(1);
            glm::vec3 x_axis = glm::vec3();

            Box() {}
            Box(const glm::vec3 &hf) : half(hf) {}
            Box(Float32 hf) : half(glm::vec3(hf, hf, hf)) {}
        };

        struct Plane
        {
            glm::vec2 size = glm::vec2(1.0f);
            glm::uvec2 subdivision = glm::uvec2(1);
            glm::vec3 x_axis = glm::vec3(1.0f, 0.0f, 0.0f);
            glm::vec3 y_axis = glm::vec3(0.0f, 1.0f, 0.0f);
        };

    public:
        static Ref<Mesh> generate(const Sphere &sphere)
        {
            Ref<Mesh> result = std::make_shared<Mesh>();

            return result;
        }

        static Ref<Mesh> generate(const Box &box)
        {
            Ref<Mesh> result = std::make_shared<Mesh>();

            return result;
        }
    };

} // namespace sgl

#endif
