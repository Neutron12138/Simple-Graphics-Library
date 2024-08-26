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

    private:
        Bool m_visible = true;

    public:
        Visual(Bool visible = true) : m_visible(visible) {}
        virtual ~Visual() = default;

    protected:
        virtual void _draw(DrawMode draw_mode = NORMAL) = 0;

    public:
        Bool get_visible() const
        {
            return m_visible;
        }

        void set_visible(Bool visible)
        {
            m_visible = visible;
        }

        Bool is_visible() const
        {
            return m_visible;
        }

        void show()
        {
            m_visible = true;
        }

        void hide()
        {
            m_visible = false;
        }

        void request_draw(DrawMode draw_mode = NORMAL)
        {
            if (m_visible)
                _draw(draw_mode);
        }
    };

} // namespace sgl

#endif
