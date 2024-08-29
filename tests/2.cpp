#include <iostream>
#include "../src/SGL.hpp"

class TriangleMaterial : public sgl::ShaderMaterial
{
public:
    sgl::Ref<sgl::UniformValueMat4> model;

public:
    TriangleMaterial() : sgl::ShaderMaterial(*sgl::ShaderMaterial::load_from_file("shaders/1.vs", "shaders/1.fs"))
    {
        model = std::make_shared<sgl::UniformValueMat4>(m_program, "model");
    }

public:
    void begin() override
    {
        m_program->use();
        model->update();
        m_program->set_uniform("color", glm::vec3(0.0, 0.0, 1.0));
    }
};

class TriangleMesh : public sgl::Mesh
{
public:
    const std::vector<glm::vec3> vertices = {
        glm::vec3(0.0f, 0.5f, 0.0f),
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),
    };

public:
    TriangleMesh()
    {
        data->vertices = vertices;
        vao = sgl::MeshTool::create_VAO(*data);

        sgl::DrawCall::DrawArrays arrays;
        arrays.mode = sgl::DrawCall::TRIANGLES;
        arrays.count = 3;
        steps->draw_calls.push_back(arrays);
    }
};

class Triangle : public sgl::MeshInstance, public sgl::Transform3D
{
public:
    Triangle()
    {
        material = std::make_shared<TriangleMaterial>();
        mesh = std::make_shared<TriangleMesh>();
    }
};

class Window : public sgl::Window
{
private:
    sgl::Ref<TriangleMaterial> material;
    sgl::Ref<Triangle> triangle;

public:
    void _initialize() override
    {
        material = std::make_shared<TriangleMaterial>();

        triangle = std::make_shared<Triangle>();
        triangle->material = material;
    }

    void _draw() override
    {
        triangle->request_draw();
    }
};

int main()
{
    try
    {
        Window window;
        return window.main_loop();
    }
    catch (const sgl::String &e)
    {
        sgl::print(e, "\n");
        return EXIT_FAILURE;
    }
}
