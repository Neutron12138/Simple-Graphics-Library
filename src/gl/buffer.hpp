#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <vector>
#include <GL/glew.h>
#include "../system/string.hpp"
#include "../base/noncopyable.hpp"

namespace sgl
{
    class Buffer : public NonCopyable
    {
    public:
        enum Type : GLenum
        {
            ARRAY = GL_ARRAY_BUFFER,
            ELEMENT_ARRAY = GL_ELEMENT_ARRAY_BUFFER,
        };

        enum Usage : GLenum
        {
            STREAM_DRAW = GL_STREAM_DRAW,
            STREAM_READ = GL_STREAM_READ,
            STREAM_COPY = GL_STREAM_COPY,

            STATIC_DRAW = GL_STATIC_DRAW,
            STATIC_READ = GL_STATIC_READ,
            STATIC_COPY = GL_STATIC_COPY,

            DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
            DYNAMIC_READ = GL_DYNAMIC_READ,
            DYNAMIC_COPY = GL_DYNAMIC_COPY,

        };

        static void unbind(Type type)
        {
            glBindBuffer(type, 0);
        }

    private:
        Type m_type;
        GLuint m_id = 0;

    public:
        Buffer(Type type) : m_type(type)
        {
            _generate_id(type);
        }

        ~Buffer()
        {
            _delete_id();
        }

    private:
        void _generate_id(Type type)
        {
            glCreateBuffers(1, &m_id);
            if (m_id == 0)
                throw to_string("Failed to create buffer, type: ", type, ".");
        }

        void _delete_id()
        {
            if (is_valid())
                glDeleteBuffers(1, &m_id);

            m_id = 0;
        }

    public:
        Type get_type() const { return m_type; }
        GLuint get_id() const { return m_id; }
        Bool is_valid() const { return m_id != 0; }

    public:
        void bind()
        {
            glBindBuffer(m_type, m_id);
        }

        void bind_data(GLsizeiptr size, const void *data, Usage usage = STATIC_DRAW)
        {
            glBufferData(m_type, size, data, usage);
        }

        template <typename T>
        void bind_data(const std::vector<T> &data, Usage usage = STATIC_DRAW)
        {
            bind_data(sizeof(T) * data.size(), data.data(), usage);
        }

        void vertex_attrib(GLuint index, GLint size, GLenum type,
                           GLboolean normalized, GLsizei stride, const void *pointer)
        {
            glVertexAttribPointer(index, size, type, normalized, stride, pointer);
            glEnableVertexAttribArray(index);
        }

        void vertex_attrib(GLuint index, GLint size, GLenum type, const void *pointer = nullptr)
        {
            GLsizei stride = size;
            switch (type)
            {
            case GL_FLOAT:
                stride *= sizeof(GLfloat);
                break;

            case GL_INT:
            case GL_UNSIGNED_INT:
                stride *= sizeof(GLint);
                break;

            default:
                break;
            }

            vertex_attrib(index, size, type, GL_FALSE, stride, pointer);
        }
    };

} // namespace sgl

#endif
