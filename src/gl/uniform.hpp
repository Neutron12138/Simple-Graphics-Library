#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include <GL/glew.h>
#include "../base/noncopyable.hpp"
#include "../base/ref.hpp"
#include "../gl/program.hpp"
#include "../system/string.hpp"

namespace sgl
{
    //
    // basic uniform
    //

    class Uniform : public NonCopyable
    {
    private:
        Ref<Program> m_program;
        String m_name;
        GLint m_location;

    public:
        Uniform(const Ref<Program> &program, const String &name)
            : m_program(program), m_name(name)
        {
            m_location = program->get_uniform_location(name);
            if (m_location == -1)
                throw to_string("Unable to get the location of the uniform (\"",
                                name, "\") in the program (ID: ", m_program->get_id(), ").");
        }

    public:
        const Ref<Program> &get_program() const
        {
            return m_program;
        }

        const String &get_name() const
        {
            return m_name;
        }

        GLint get_location() const
        {
            return m_location;
        }
    };

    //
    // uniform with value
    //

    template <typename T>
    class UniformValue : public Uniform
    {
    public:
        T value;

    public:
        UniformValue(const Ref<Program> &program, const String &name)
            : Uniform(program, name) {}

    public:
        virtual void update()
        {
            get_program()->set_uniform(get_location(), value);
        }
    };

    using UniformValueVec2 = UniformValue<glm::vec2>;
    using UniformValueVec3 = UniformValue<glm::vec3>;
    using UniformValueVec4 = UniformValue<glm::vec4>;
    using UniformValueMat4 = UniformValue<glm::mat4>;

} // namespace sgl

#endif
