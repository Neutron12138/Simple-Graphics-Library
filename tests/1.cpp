#include <iostream>
#include "../src/SGL.hpp"

class Window : public sgl::Window
{
private:
    sgl::Debugger m_dbg;

protected:
    void _process(double delta) override
    {
    }

    void _draw() override
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
};

int main()
{
    Window window;
    window.main_loop();
    return 0;
}