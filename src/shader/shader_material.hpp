#ifndef SHADER_MATERIAL_HPP
#define SHADER_MATERIAL_HPP

#include "material.hpp"

namespace sgl
{
    class ShaderMaterial : public Material
    {
    public:
        static Ref<ShaderMaterial> load_from_file(const String &vpath, const String &fpath, Bool output = true)
        {
            Ref<Shader> vshader = Shader::load_from_file(Shader::VERTEX, vpath, output);
            Ref<Shader> fshader = Shader::load_from_file(Shader::FRAGMENT, fpath, output);

            Ref<ShaderMaterial> result = std::make_shared<ShaderMaterial>();
            result->get_program()->link_shaders(*vshader, *fshader);

            return result;
        }

    protected:
        Ref<Program> m_program;

    public:
        ShaderMaterial() : m_program(std::make_shared<Program>()) {}
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
