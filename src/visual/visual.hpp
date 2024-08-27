#ifndef VISUAL_HPP
#define VISUAL_HPP

#include "../base/type.hpp"

namespace sgl
{
    class Visual
    {
    public:
        enum DrawMode
        {
            NORMAL,
            DEPTH,
            UNSHADED,
        };

    public:
        Bool visible = true;

    public:
        Visual(Bool v = true) : visible(v) {}
        virtual ~Visual() = default;

    protected:
        virtual void _draw(DrawMode draw_mode = NORMAL) = 0;

    public:
        void show() { visible = true; }
        void hide() { visible = false; }

        void request_draw(DrawMode draw_mode = NORMAL)
        {
            if (visible)
                _draw(draw_mode);
        }
    };

} // namespace sgl

#endif
