#ifndef MESH_TOOL_HPP
#define MESH_TOOL_HPP

#include "mesh.hpp"

namespace sgl
{
    class MeshTool
    {
    public:
        static void bind_VAO(MeshVAO &vao, const MeshData &data, Buffer::Usage usage = Buffer::STATIC_DRAW)
        {
            if (!data.vertices.empty())
                vao.vertices->bind_vertices(Program::POSITION, data.vertices, usage);

            if (!data.normals.empty())
                vao.normals->bind_vertices(Program::NORMAL, data.normals, usage);

            if (!data.texCoords.empty())
                vao.texCoords->bind_vertices(Program::TEXCOORD, data.texCoords, usage);

            if (!data.colors.empty())
                vao.colors->bind_vertices(Program::COLOR, data.colors, usage);

            if (!data.elements.empty())
            {
                vao.elements->bind();
                vao.elements->bind_data(data.elements, usage);
            }
        }

        static void bind_VAO_ext(MeshVAOExt &vao, const MeshDataExt &data, Buffer::Usage usage = Buffer::STATIC_DRAW)
        {
            bind_VAO(vao, data);

            if (!data.texCoords2.empty())
                vao.texCoords2->bind_vertices(Program::TEXCOORD2, data.texCoords2, usage);

            if (!data.texCoords2.empty())
                vao.custom0->bind_vertices(Program::CUSTOM0, data.custom0, usage);

            if (!data.texCoords2.empty())
                vao.custom1->bind_vertices(Program::CUSTOM1, data.custom1, usage);

            if (!data.texCoords2.empty())
                vao.custom2->bind_vertices(Program::CUSTOM2, data.custom2, usage);

            if (!data.texCoords2.empty())
                vao.custom3->bind_vertices(Program::CUSTOM3, data.custom3, usage);

            if (!data.matrices.empty())
                vao.matrices->bind_vertices(Program::MATRIX, data.matrices, usage);
        }

        static Ref<MeshVAO> create_VAO(const MeshData &data, Buffer::Usage usage = Buffer::STATIC_DRAW)
        {
            Ref<MeshVAO> result = std::make_shared<MeshVAO>();
            result->vao->bind();
            bind_VAO(*result, data, usage);
            result->vao->unbind();
            return result;
        }

        static Ref<MeshVAOExt> create_VAO_ext(const MeshDataExt &data, Buffer::Usage usage = Buffer::STATIC_DRAW)
        {
            Ref<MeshVAOExt> result = std::make_shared<MeshVAOExt>();
            result->vao->bind();
            bind_VAO_ext(*result, data, usage);
            result->vao->unbind();
            return result;
        }
    };

} // namespace sgl

#endif
