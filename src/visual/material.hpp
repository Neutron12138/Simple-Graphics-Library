#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "../gl/program.hpp"
#include "../base/ref.hpp"

namespace sgl
{
    //
    // 材质抽象基类
    //

    class Material
    {
    public:
        virtual ~Material() = default;

    public:
        virtual void begin() = 0;
        virtual void end() = 0;
    };

    //
    // 含有着色器的材质
    //

    class ShaderMaterial : public Material
    {
    protected:
        Ref<Program> m_program;

    public:
        ShaderMaterial() {}
        ShaderMaterial(const Ref<Program> &program) : m_program(program) {}

    public:
        const Ref<Program> &get_program() const
        {
            return m_program;
        }

    public:
        void begin() override
        {
            m_program->use();
        }

        void end() override
        {
            m_program->unuse();
        }
    };

} // namespace sgl

#endif
