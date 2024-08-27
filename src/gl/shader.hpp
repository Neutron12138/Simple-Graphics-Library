#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include "../system/string.hpp"
#include "../base/noncopyable.hpp"

namespace sgl
{
    class Shader : public NonCopyable
    {
    public:
        enum Type : GLenum
        {
            VERTEX = GL_VERTEX_SHADER,
            FRAGMENT = GL_FRAGMENT_SHADER,
            GEOMETRY = GL_GEOMETRY_SHADER,
            COMPUTE = GL_COMPUTE_SHADER,
        };

        static Ref<Shader> load_from_file(Type type, const String &path, Bool output = true)
        {
            Ref<Shader> result = std::make_shared<Shader>(type);
            if (result->load_from_file(path, output))
                return result;
            else
                return nullptr;
        }

    private:
        Type m_type;
        GLuint m_id = 0;

    public:
        Shader(Type type) : m_type(type)
        {
            _generate_id(type);
        }

        ~Shader()
        {
            _delete_id();
        }

    private:
        void _generate_id(Type type)
        {
            m_id = glCreateShader(type);
            if (m_id == 0)
                throw to_string("Failed to create shader, type: ", type, ".");
        }

        void _delete_id()
        {
            if (is_valid())
                glDeleteShader(m_id);

            m_id = 0;
        }

    public:
        Type get_type() const
        {
            return m_type;
        }

        GLuint get_id() const
        {
            return m_id;
        }

        Bool is_valid() const
        {
            return m_id != 0;
        }

    public:
        void set_source(const String &source)
        {
            const GLchar *str = source.data();
            glShaderSource(m_id, 1, &str, nullptr);
        }

        Bool compile_shader(bool output = true)
        {
            glCompileShader(m_id);

            Int32 success = 0;
            glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

            if (!success && output)
            {
                Int32 length = 0;
                glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &length);
                String error(length, 0);
                glGetShaderInfoLog(m_id, length, nullptr, error.data());
                sgl::print(error);
            }

            return success;
        }

        Bool load_from_string(const String &source, Bool output = true)
        {
            set_source(source);
            return compile_shader();
        }

        Bool load_from_stream(std::istream &is, Bool output = true)
        {
            String source = load_stream_text(is);
            return load_from_string(source);
        }

        Bool load_from_file(const String &path, Bool output = true)
        {
            String source = load_file_text(path);
            return load_from_string(source);
        }
    };

} // namespace sgl

#endif
