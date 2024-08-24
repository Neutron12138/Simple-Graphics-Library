#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "shader.hpp"

namespace sgl
{
    class Program : public NonCopyable
    {
    public:
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
    };

} // namespace sgl

#endif
