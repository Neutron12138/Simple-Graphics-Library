#include <iostream>
#include "../src/SGL.hpp"

class Window : public sgl::Window
{
private:
    sgl::Debugger dbg;
    sgl::Ref<sgl::Program> program;
    sgl::Ref<sgl::Shader> vshader;
    sgl::Ref<sgl::Shader> fshader;
    sgl::Ref<sgl::Buffer> vbo;
    sgl::Ref<sgl::VertexArray> vao;

protected:
    void _initialize() override
    {
        vshader = std::make_shared<sgl::Shader>(sgl::Shader::VERTEX);
        vshader->load_from_file("shaders/1.vs", false);

        fshader = std::make_shared<sgl::Shader>(sgl::Shader::FRAGMENT);
        fshader->load_from_file("shaders/1.fs", false);

        program = std::make_shared<sgl::Program>();
        program->link_shaders(*vshader, *fshader);
        program->use();

        GLfloat vertices[] = {
            0.0f,
            0.5f,
            0.0f,

            -0.5f,
            -0.5f,
            0.0f,

            0.5f,
            -0.5f,
            0.0f,
        };

        vao = std::make_shared<sgl::VertexArray>();
        vao->bind();

        vbo = std::make_shared<sgl::Buffer>(sgl::Buffer::ARRAY);
        vbo->bind();
        vbo->bind_data(sizeof(vertices), vertices, sgl::Buffer::STATIC_DRAW);
        vbo->vertex_attrib(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    }

    void _draw() override
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};

int main()
{
    try
    {
        Window window;
        window.main_loop();
    }
    catch (const sgl::String &e)
    {
        sgl::print(e, "\n");
    }

    return 0;
}