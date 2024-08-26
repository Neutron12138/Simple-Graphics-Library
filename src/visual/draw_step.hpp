#ifndef DRAW_STEP_HPP
#define DRAW_STEP_HPP

#include <GL/glew.h>

namespace sgl
{
    class DrawStep
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
            ELEMENTS,
        };

        struct DrawArrays
        {
            Mode mode = POINTS;
            GLint first = 0;
            GLsizei count = 0;
        };

        struct DrawElements
        {
            Mode mode = POINTS;
            GLsizei count = 0;
            Type type = UNSIGNED_INT;
            const void *indices = nullptr;
        };

    public:
        DrawMethod method = ARRAYS;
        union
        {
            DrawArrays arrays;
            DrawElements elements;
        };

    public:
        DrawStep() {}
        DrawStep(const DrawArrays &arr) : method(ARRAYS), arrays(arr) {}
        DrawStep(const DrawElements &elem) : method(ELEMENTS), elements(elem) {}

    public:
        virtual void draw()
        {
            switch (method)
            {
            case ARRAYS:
                glDrawArrays(arrays.mode, arrays.first, arrays.count);
                break;

            case ELEMENTS:
                glDrawElements(elements.mode, elements.count, elements.type, elements.indices);
                break;

            default:
                break;
            }
        }
    };

} // namespace sgl

#endif
