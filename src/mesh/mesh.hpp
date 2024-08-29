#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <glm/glm.hpp>
#include "../gl/vertex_array.hpp"
#include "../gl/buffer.hpp"
#include "../base/ref.hpp"
#include "../gl/program.hpp"
#include "../visual/draw_steps.hpp"

namespace sgl
{
    //
    // 基本版
    //

    struct MeshVAO
    {
        Ref<VertexArray> vao = std::make_shared<VertexArray>();

        Ref<Buffer> vertices = std::make_shared<Buffer>(Buffer::ARRAY);
        Ref<Buffer> normals = std::make_shared<Buffer>(Buffer::ARRAY);
        Ref<Buffer> texCoords = std::make_shared<Buffer>(Buffer::ARRAY);
        Ref<Buffer> colors = std::make_shared<Buffer>(Buffer::ARRAY);
        Ref<Buffer> elements = std::make_shared<Buffer>(Buffer::ELEMENT_ARRAY);

        MeshVAO() {}
    };

    struct MeshData
    {
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords;
        std::vector<glm::vec4> colors;
        std::vector<GLuint> elements;

        MeshData() {}
    };

    struct Mesh
    {
        Ref<MeshVAO> vao = std::make_shared<MeshVAO>();
        Ref<MeshData> data = std::make_shared<MeshData>();
        Ref<DrawSteps> steps = std::make_shared<DrawSteps>();

        Mesh() {}
    };

    //
    // 拓展版
    //

    struct MeshVAOExt : public MeshVAO
    {
        Ref<Buffer> texCoords2 = std::make_shared<Buffer>(Buffer::ARRAY);
        Ref<Buffer> custom0 = std::make_shared<Buffer>(Buffer::ARRAY);
        Ref<Buffer> custom1 = std::make_shared<Buffer>(Buffer::ARRAY);
        Ref<Buffer> custom2 = std::make_shared<Buffer>(Buffer::ARRAY);
        Ref<Buffer> custom3 = std::make_shared<Buffer>(Buffer::ARRAY);
        Ref<Buffer> matrices = std::make_shared<Buffer>(Buffer::ARRAY);

        MeshVAOExt() {}
    };

    struct MeshDataExt : public MeshData
    {
        std::vector<glm::vec2> texCoords2;
        std::vector<glm::vec4> custom0;
        std::vector<glm::vec4> custom1;
        std::vector<glm::vec4> custom2;
        std::vector<glm::vec4> custom3;
        std::vector<glm::mat4> matrices;

        MeshDataExt() {}
    };

    struct MeshExt
    {
        Ref<MeshVAOExt> vao = std::make_shared<MeshVAOExt>();
        Ref<MeshDataExt> data = std::make_shared<MeshDataExt>();
        Ref<DrawSteps> steps = std::make_shared<DrawSteps>();

        MeshExt() {}
    };

} // namespace sgl

#endif
