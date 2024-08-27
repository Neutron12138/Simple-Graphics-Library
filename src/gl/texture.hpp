#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include "../base/noncopyable.hpp"

namespace sgl
{
    class Texture : public NonCopyable
    {
    public:
        enum Type : GLenum
        {
            TEXTURE_2D = GL_TEXTURE_2D,
        };

        enum Wrap : GLenum
        {
            REPEAT = GL_REPEAT,
            MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
            CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
            CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,

        };

        enum Filter : GLenum
        {
            NEAREST = GL_NEAREST,
            LINEAR = GL_LINEAR,
            NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
            LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
            NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
            LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
        };

        enum Format : GLenum
        {
            RED = GL_RED,
            RG = GL_RG,
            RGB = GL_RGB,
            RGBA = GL_RGBA,
        };

        enum DataType
        {
            BYTE = GL_BYTE,
            UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
        };

        static void unbind(Type type)
        {
            glBindTexture(type, 0);
        }

    private:
        Type m_type;
        GLuint m_id = 0;

    public:
        Texture(Type type) : m_type(type)
        {
            _generate_id(type);
        }

        ~Texture()
        {
            _delete_id();
        }

    private:
        void _generate_id(Type type)
        {
            glGenTextures(1, &m_id);
            if (m_id == 0)
                throw to_string("Failed to create texture, type: ", type, ".");
        }

        void _delete_id()
        {
            if (is_valid())
                glDeleteShader(m_id);

            m_id = 0;
        }

    public:
        Type get_type() const { return m_type; }
        GLuint get_id() const { return m_id; }
        Bool is_valid() const { return m_id != 0; }

    public:
        void bind()
        {
            glBindTexture(m_type, m_id);
        }
    };

} // namespace sgl

#endif
