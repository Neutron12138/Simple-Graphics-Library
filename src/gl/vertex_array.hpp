#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include <GL/glew.h>
#include "../system/string.hpp"
#include "../base/noncopyable.hpp"

namespace sgl
{
    class VertexArray : public NonCopyable
    {
    public:
        static void unbind()
        {
            glBindVertexArray(0);
        }

    private:
        GLuint m_id;

    public:
        VertexArray()
        {
            _generate_id();
        }

        ~VertexArray()
        {
            _delete_id();
        }

    private:
        void _generate_id()
        {
            glCreateVertexArrays(1, &m_id);
            if (m_id == 0)
                throw to_string("Failed to create vertex array.");
        }

        void _delete_id()
        {
            if (is_valid())
                glDeleteVertexArrays(1, &m_id);

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
        void bind()
        {
            glBindVertexArray(m_id);
        }
    };

} // namespace sgl

#endif
