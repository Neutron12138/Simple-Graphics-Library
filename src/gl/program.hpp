#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include <glm/glm.hpp>
#include "shader.hpp"

namespace sgl
{
    class Program : public NonCopyable
    {
    public:
        enum DefaultAttribLocation
        {
            POSITION,
            NORMAL,
            TEXCOORD,
            TEXCOORD2,
            COLOR,

            CUSTOM0,
            CUSTOM1,
            CUSTOM2,
            CUSTOM3,

            COUNT,
        };

        static void unuse()
        {
            glUseProgram(0);
        }

    private:
        GLuint m_id;

    public:
        Program()
        {
            _generate_id();
        }

        ~Program()
        {
            _delete_id();
        }

    private:
        void _generate_id()
        {
            m_id = glCreateProgram();
            if (m_id == 0)
                throw to_string("Failed to create program.");
        }

        void _delete_id()
        {
            if (is_valid())
                glDeleteShader(m_id);

            m_id = 0;
        }

    public:
        GLuint get_id() const
        {
            return m_id;
        }

        Bool is_valid() const
        {
            return m_id != 0;
        }

    public:
        void use()
        {
            glUseProgram(m_id);
        }

        void attach_shader(const Shader &shader)
        {
            if (is_valid() && shader.is_valid())
                glAttachShader(m_id, shader.get_id());
            else
                throw to_string("Unable to attach invalid object, program ID: ",
                                m_id, ", shader ID: ", shader.get_id(), ".");
        }

        Bool link_program(bool output = true)
        {
            glLinkProgram(m_id);

            Int32 success = 0;
            glGetProgramiv(m_id, GL_LINK_STATUS, &success);

            if (!success && output)
            {
                Int32 length;
                glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
                String info_log(length, 0);
                glGetProgramInfoLog(m_id, length, nullptr, info_log.data());
                sgl::print(info_log, "\n");
            }

            return success;
        }

        Bool link_shaders(const Shader &vshader, const Shader &fshader)
        {
            attach_shader(vshader);
            attach_shader(fshader);
            return link_program();
        }

        Bool link_shaders(const Shader &vshader, const Shader &fshader, const Shader &gshader)
        {
            attach_shader(vshader);
            attach_shader(fshader);
            attach_shader(gshader);
            return link_program();
        }

        GLint get_uniform_location(const String &name)
        {
            return glGetUniformLocation(m_id, name.data());
        }

        GLint get_attrib_location(const String &name)
        {
            return glGetAttribLocation(m_id, name.data());
        }

    public:
        void set_uniform(const String &name, const glm::vec2 &value)
        {
            GLint location = get_uniform_location(name);
            glUniform2f(location, value.x, value.y);
        }

        void set_uniform(const String &name, const glm::vec3 &value)
        {
            GLint location = get_uniform_location(name);
            glUniform3f(location, value.x, value.y, value.z);
        }

        void set_uniform(const String &name, const glm::vec4 &value)
        {
            GLint location = get_uniform_location(name);
            glUniform4f(location, value.x, value.y, value.z, value.w);
        }
    };

} // namespace sgl

#endif
