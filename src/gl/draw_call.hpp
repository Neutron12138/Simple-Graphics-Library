#ifndef DRAW_CALL_HPP
#define DRAW_CALL_HPP

#include <GL/glew.h>

namespace sgl
{
    class DrawCall
    {
    public:
        enum Mode : GLenum
        {
            POINTS = GL_POINTS,

            LINES = GL_LINES,
            LINE_STRIP = GL_LINE_STRIP,
            LINE_LOOP = GL_LINE_LOOP,

            TRIANGLES = GL_TRIANGLES,
            TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
            TRIANGLE_FAN = GL_TRIANGLE_FAN,
        };

        enum Type : GLenum
        {
            INT = GL_INT,
            UNSIGNED_INT = GL_UNSIGNED_INT,
        };

        enum DrawMethod
        {
            ARRAYS,
            ARRAYS_INSTANCED,
            ELEMENTS,
            ELEMENTS_INSTANCED,
        };

        struct DrawArrays
        {
            Mode mode = POINTS;
            GLint first = 0;
            GLsizei count = 0;

            DrawArrays() {}
        };

        struct DrawArraysInstanced : public DrawArrays
        {
            GLsizei primcount = 0;

            DrawArraysInstanced() {}
        };

        struct DrawElements
        {
            Mode mode = POINTS;
            GLsizei count = 0;
            Type type = UNSIGNED_INT;
            const void *indices = nullptr;

            DrawElements() {}
        };

        struct DrawElementsInstanced : public DrawElements
        {
            GLsizei primcount = 0;

            DrawElementsInstanced() {}
        };

    public:
        DrawMethod method;
        union
        {
            DrawArrays arrays;
            DrawElements elements;
            DrawArraysInstanced arrays_instanced;
            DrawElementsInstanced elements_instanced;
        };

    public:
        DrawCall(const DrawArrays &data = {}) : method(ARRAYS), arrays(data) {}
        DrawCall(const DrawArraysInstanced &data) : method(ARRAYS_INSTANCED), arrays_instanced(data) {}
        DrawCall(const DrawElements &data) : method(ELEMENTS), elements(data) {}
        DrawCall(const DrawElementsInstanced &data) : method(ELEMENTS_INSTANCED), elements_instanced(data) {}

    public:
        void draw()
        {
            switch (method)
            {
            case ARRAYS:
                glDrawArrays(arrays.mode, arrays.first, arrays.count);
                break;

            case ARRAYS_INSTANCED:
                glDrawArraysInstanced(arrays_instanced.mode, arrays_instanced.first,
                                      arrays_instanced.count, arrays_instanced.primcount);
                break;

            case ELEMENTS:
                glDrawElements(elements.mode, elements.count, elements.type, elements.indices);
                break;

            case ELEMENTS_INSTANCED:
                glDrawElementsInstanced(elements_instanced.mode, elements_instanced.count, elements_instanced.type,
                                        elements_instanced.indices, elements_instanced.primcount);
                break;
            }
        }
    };

} // namespace sgl

#endif
