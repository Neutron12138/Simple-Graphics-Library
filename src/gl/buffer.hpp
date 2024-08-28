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

        enum DataType : GLenum
        {
            FLOAT = GL_FLOAT,
            INT = GL_INT,
            UNSIGNED_INT = GL_UNSIGNED_INT,
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

        void vertex_attrib(GLuint index, GLint size, DataType type, GLboolean normalized,
                           GLsizei stride, const void *pointer = nullptr, GLuint divisor = 0)
        {
            glVertexAttribPointer(index, size, type, normalized, stride, pointer);
            glEnableVertexAttribArray(index);
            glVertexAttribDivisor(index, divisor);
        }

        void vertex_attrib(GLuint index, GLint size, const void *pointer = nullptr, GLuint divisor = 0)
        {
            vertex_attrib(index, size, FLOAT, GL_FALSE, size * sizeof(GLfloat), pointer, divisor);
        }

    public:
        void bind_vertices(GLuint index, const std::vector<glm::vec2> &vertices, Usage usage = STATIC_DRAW)
        {
            bind();
            bind_data(vertices, usage);
            vertex_attrib(index, 2);
        }

        void bind_vertices(GLuint index, const std::vector<glm::vec3> &vertices, Usage usage = STATIC_DRAW)
        {
            bind();
            bind_data(vertices, usage);
            vertex_attrib(index, 3);
        }

        void bind_vertices(GLuint index, const std::vector<glm::vec4> &vertices, Usage usage = STATIC_DRAW)
        {
            bind();
            bind_data(vertices, usage);
            vertex_attrib(index, 4);
        }

        void bind_vertices(GLuint index, const std::vector<glm::mat4> &matrices, Usage usage = STATIC_DRAW)
        {
            bind();
            bind_data(matrices, usage);
            vertex_attrib(index + 0, 4, nullptr, 1);
            vertex_attrib(index + 1, 4, nullptr, 1);
            vertex_attrib(index + 2, 4, nullptr, 1);
            vertex_attrib(index + 3, 4, nullptr, 1);
        }
    };

} // namespace sgl

#endif
