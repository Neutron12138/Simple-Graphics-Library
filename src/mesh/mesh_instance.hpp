#ifndef MESH_INSTANCE_HPP
#define MESH_INSTANCE_HPP

#include "../visual/visual.hpp"
#include "../shader/material.hpp"
#include "../mesh/mesh.hpp"
#include "../visual/draw_step.hpp"

namespace sgl
{
    //
    // 普通的网格实例
    //

    class MeshInstance : public Visual
    {
    public:
        Ref<Material> material;
        Ref<MeshVAO> vao;

    public:
        MeshInstance() {}
        MeshInstance(const Ref<Material> &mat,
                     const Ref<MeshVAO> &va) : material(mat),
                                               vao(va) {}
    };

    //
    // 绘制图元的网格实例
    //

    class PrimitiveMeshInstance : public MeshInstance
    {
    public:
        Ref<DrawStep> draw_step;

    public:
        PrimitiveMeshInstance() {}
        PrimitiveMeshInstance(const Ref<Material> &mat,
                              const Ref<MeshVAO> &va,
                              const Ref<DrawStep> &step) : MeshInstance(mat, va),
                                                           draw_step(step) {}

    protected:
        void _draw(DrawMode draw_mode) override
        {
            material->begin();
            vao->vertex_array->bind();

            draw_step->draw();

            material->end();
            vao->vertex_array->unbind();
        }
    };

} // namespace sgl

#endif
