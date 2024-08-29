#ifndef MESH_INSTANCE_HPP
#define MESH_INSTANCE_HPP

#include "../visual/visual.hpp"
#include "../shader/material.hpp"
#include "../mesh/mesh.hpp"
#include "../visual/draw_steps.hpp"

namespace sgl
{
    class MeshInstance : public Visual
    {
    public:
        Ref<Material> material = nullptr;
        Ref<Mesh> mesh = std::make_shared<Mesh>();

    public:
        MeshInstance() {}
        MeshInstance(const Ref<Material> &mat,
                     const Ref<Mesh> &m) : material(mat),
                                           mesh(m) {}

    protected:
        void _draw(DrawMode draw_mode) override
        {
            material->begin();
            mesh->vao->vao->bind();

            mesh->steps->draw();

            material->end();
            mesh->vao->vao->unbind();
        }
    };

    class MeshExtInstance : public Visual
    {
    public:
        Ref<Material> material = nullptr;
        Ref<MeshExt> mesh = std::make_shared<MeshExt>();

    public:
        MeshExtInstance() {}
        MeshExtInstance(const Ref<Material> &mat,
                        const Ref<MeshExt> &m) : material(mat),
                                                 mesh(m) {}

    protected:
        void _draw(DrawMode draw_mode) override
        {
            material->begin();
            mesh->vao->vao->bind();

            mesh->steps->draw();

            material->end();
            mesh->vao->vao->unbind();
        }
    };

} // namespace sgl

#endif
