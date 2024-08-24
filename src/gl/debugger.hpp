#ifndef DEBUGGER_HPP
#define DEBUGGER_HPP

#include <GL/glew.h>
#include "../system/string.hpp"

namespace sgl
{
    class Debugger
    {
    public:
        static void debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                   GLsizei length, const GLchar *message, const void *userParam)
        {
            void *ptr = const_cast<void *>(userParam);
            Debugger *dbg = reinterpret_cast<Debugger *>(ptr);
            dbg->debug(source, type, id, severity, length, message);
        }

    public:
        Debugger()
        {
            glDebugMessageCallback(debug_callback, this);
        }

    public:
        virtual void debug(GLenum source, GLenum type, GLuint id, GLenum severity,
                           GLsizei length, const GLchar *message)
        {
            sgl::print(message, "\n");
        }
    };

} // namespace sgl

#endif
