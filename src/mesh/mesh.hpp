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
    //
    // 基本版
    //

    struct MeshVAO
    {
        Ref<VertexArray> vao;

        Ref<Buffer> vertices;
        Ref<Buffer> normals;
        Ref<Buffer> texCoords;
        Ref<Buffer> colors;
        Ref<Buffer> elements;

        MeshVAO()
        {
            vao = std::make_shared<VertexArray>();

            vertices = std::make_shared<Buffer>(Buffer::ARRAY);
            normals = std::make_shared<Buffer>(Buffer::ARRAY);
            texCoords = std::make_shared<Buffer>(Buffer::ARRAY);
            colors = std::make_shared<Buffer>(Buffer::ARRAY);
            elements = std::make_shared<Buffer>(Buffer::ELEMENT_ARRAY);
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

    //
    // 拓展版
    //

    struct MeshVAOExt : public MeshVAO
    {
        Ref<Buffer> texCoords2;
        Ref<Buffer> custom0;
        Ref<Buffer> custom1;
        Ref<Buffer> custom2;
        Ref<Buffer> custom3;
        Ref<Buffer> matrices;

        MeshVAOExt() : MeshVAO()
        {
            texCoords2 = std::make_shared<Buffer>(Buffer::ARRAY);
            custom0 = std::make_shared<Buffer>(Buffer::ARRAY);
            custom1 = std::make_shared<Buffer>(Buffer::ARRAY);
            custom2 = std::make_shared<Buffer>(Buffer::ARRAY);
            custom3 = std::make_shared<Buffer>(Buffer::ARRAY);
            matrices = std::make_shared<Buffer>(Buffer::ARRAY);
        }
    };

    struct MeshDataExt : public MeshData
    {
        std::vector<glm::vec2> texCoords2;
        std::vector<glm::vec4> custom0;
        std::vector<glm::vec4> custom1;
        std::vector<glm::vec4> custom2;
        std::vector<glm::vec4> custom3;
        std::vector<glm::mat4> matrices;
    };

} // namespace sgl

#endif
