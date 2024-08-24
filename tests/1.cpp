#include <iostream>
#include "../src/SGL.hpp"

class Triangle : public sgl::Visual
{
public:
    const std::vector<glm::vec3> vertices = {
        glm::vec3(0.0f, 0.5f, 0.0f),
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),
    };

private:
    sgl::Ref<sgl::Program> program;
    sgl::Ref<sgl::Shader> vshader;
    sgl::Ref<sgl::Shader> fshader;
    sgl::Ref<sgl::MeshData> mesh;
    sgl::Ref<sgl::MeshVAO> vao;

public:
    Triangle()
    {
        vshader = std::make_shared<sgl::Shader>(sgl::Shader::VERTEX);
        vshader->load_from_file("shaders/1.vs", false);

        fshader = std::make_shared<sgl::Shader>(sgl::Shader::FRAGMENT);
        fshader->load_from_file("shaders/1.fs", false);

        program = std::make_shared<sgl::Program>();
        program->link_shaders(*vshader, *fshader);
        program->use();

        mesh = std::make_shared<sgl::MeshData>();
        mesh->vertices = vertices;

        vao = sgl::create_VAO(*mesh);
        vao->vertex_array->bind();
    }

protected:
    void _draw(DrawMode draw_mode)
    {
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};

class Window : public sgl::Window
{
private:
    sgl::Ref<sgl::Debugger> debugger;
    sgl::Ref<Triangle> triangle;

protected:
    void _initialize() override
    {
        debugger = std::make_shared<sgl::Debugger>();
        triangle = std::make_shared<Triangle>();
    }

    void _draw() override
    {
        glClear(GL_COLOR_BUFFER_BIT);
        triangle->request_draw();
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