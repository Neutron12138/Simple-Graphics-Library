#ifndef DRAW_STEPS_HPP
#define DRAW_STEPS_HPP

#include <vector>
#include <initializer_list>
#include "../gl/draw_call.hpp"

namespace sgl
{
    class DrawSteps
    {
    public:
        std::vector<DrawCall> draw_calls = {};

    public:
        DrawSteps(const std::vector<DrawCall> &dc = {}) : draw_calls(dc) {}
        DrawSteps(const std::initializer_list<DrawCall> &dc) : draw_calls(dc) {}

    public:
        void draw()
        {
            for (SizeT i = 0; i < draw_calls.size(); i++)
                draw_calls[i].draw();
        }
    };

} // namespace sgl

#endif
