#ifndef SHADER_MATERIAL_HPP
#define SHADER_MATERIAL_HPP

#include "material.hpp"

namespace sgl
{
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
