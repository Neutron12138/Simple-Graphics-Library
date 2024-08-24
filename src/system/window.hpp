#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include "time.hpp"
#include "string.hpp"

namespace sgl
{
    class Window
    {
    public:
        sf::ContextSettings DEFAULT_CONTEXT_SETTINGS =
            sf::ContextSettings(
                24, 8, 8, 4, 6,
                sf::ContextSettings::Attribute::Core | sf::ContextSettings::Attribute::Debug);

    protected:
        sf::RenderWindow m_window;
        Float64 m_last_frame = 0.0f;
        Float64 m_delta = 0.0f;

    public:
        Window(const std::string &title = "", UInt32 width = 1152, UInt32 height = 648)
            : m_window(sf::VideoMode(width, height), title,
                       sf::Style::Default,
                       DEFAULT_CONTEXT_SETTINGS)
        {
            GLenum result = glewInit();
            if (result != GLEW_OK)
                throw to_string("Failed to initialize glew，result: ", result, ".");
        }

    protected:
        virtual void _initialize() {}
        virtual void _process(Float64 delta) {}
        virtual void _draw() {}

    protected:
        void _calc_delta()
        {
            Float64 current_frame = get_current_time();
            m_delta = current_frame - m_last_frame;
            m_last_frame = current_frame;
        }

        virtual void _handle_event(sf::Event event)
        {
            switch (event.type)
            {
            case sf::Event::EventType::Closed:
                m_window.close();
                break;
            }
        }

        virtual void _process_frame()
        {
            _calc_delta();

            sf::Event event;
            while (m_window.pollEvent(event))
            {
                _handle_event(event);
            }

            _process(m_delta);
            _draw();
            m_window.display();
        }

    public:
        void main_loop()
        {
            m_last_frame = get_current_time();
            _initialize();
            while (m_window.isOpen())
            {
                _process_frame();
            }
        }
    };

} // namespace sgl

#endif
