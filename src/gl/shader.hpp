#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>

namespace sgl
{
    class Shader
    {
    public:
        enum Type
        {
            VERTEX = GL_VERTEX_SHADER,
            FRAGMENT = GL_FRAGMENT_SHADER,
            GEOMETRY = GL_GEOMETRY_SHADER,
        };

    private:
        GLuint m_id;

    public:
        Shader(Type type)
        {
            m_id = glCreateShader(type);
        }
    };

} // namespace sgl

#endif
