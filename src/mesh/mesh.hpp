#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <glm/glm.hpp>
#include "../gl/vertex_array.hpp"
#include "../gl/buffer.hpp"
#include "../base/ref.hpp"
#include "../gl/program.hpp"

namespace sgl
{
    struct MeshVAO
    {
        Ref<VertexArray> vertex_array;

        Ref<Buffer> vertices_buffer;
        Ref<Buffer> normals_buffer;
        Ref<Buffer> texCoords_buffer;
        Ref<Buffer> colors_buffer;
        Ref<Buffer> elements_buffer;

        MeshVAO()
        {
            vertex_array = std::make_shared<VertexArray>();

            vertices_buffer = std::make_shared<Buffer>(Buffer::ARRAY);
            normals_buffer = std::make_shared<Buffer>(Buffer::ARRAY);
            texCoords_buffer = std::make_shared<Buffer>(Buffer::ARRAY);
            colors_buffer = std::make_shared<Buffer>(Buffer::ARRAY);
            elements_buffer = std::make_shared<Buffer>(Buffer::ELEMENT_ARRAY);
        }
    };

    struct MeshData
    {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords;
        std::vector<glm::vec4> colors;
        std::vector<GLuint> elements;
    };

    Ref<MeshVAO> create_VAO(const MeshData &data, Buffer::Usage usage = Buffer::STATIC_DRAW)
    {
        Ref<MeshVAO> vao;
        vao = std::make_shared<MeshVAO>();

        vao->vertex_array->bind();

        if (!data.vertices.empty())
        {
            vao->vertices_buffer->bind();
            vao->vertices_buffer->bind_data(data.vertices, usage);
            vao->vertices_buffer->vertex_attrib(Program::POSITION, 3, GL_FLOAT);
        }

        if (!data.normals.empty())
        {
            vao->normals_buffer->bind();
            vao->normals_buffer->bind_data(data.normals, usage);
            vao->normals_buffer->vertex_attrib(Program::NORMAL, 3, GL_FLOAT);
        }

        if (!data.texCoords.empty())
        {
            vao->texCoords_buffer->bind();
            vao->texCoords_buffer->bind_data(data.texCoords, usage);
            vao->texCoords_buffer->vertex_attrib(Program::TEXCOORD, 2, GL_FLOAT);
        }

        if (!data.colors.empty())
        {
            vao->colors_buffer->bind();
            vao->colors_buffer->bind_data(data.colors, usage);
            vao->colors_buffer->vertex_attrib(Program::COLOR, 4, GL_FLOAT);
        }

        if (!data.elements.empty())
        {
            vao->elements_buffer->bind();
            vao->elements_buffer->bind_data(data.elements, usage);
        }

        vao->vertex_array->unbind();

        return vao;
    }

} // namespace sgl

#endif
