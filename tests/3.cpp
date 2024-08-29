#include <iostream>
#include "../src/SGL.hpp"

class Rect : public sgl::MeshInstance
{
public:
    const std::vector<glm::vec3> vertices = {
        glm::vec3(-1.0, 1.0, 0.0),
        glm::vec3(-1.0, -1.0, 0.0),
        glm::vec3(1.0, -1.0, 0.0),
        glm::vec3(1.0, 1.0, 0.0),
    };

    const std::vector<glm::vec2> texCoords = {
        glm::vec2(0.0, 0.0),
        glm::vec2(0.0, 1.0),
        glm::vec2(1.0, 1.0),
        glm::vec2(1.0, 0.0),
    };

private:
    sgl::Ref<sgl::Texture2D> texture;

public:
    Rect()
    {
        mesh->data->vertices = vertices;
        mesh->data->texCoords = texCoords;
        mesh->vao = sgl::MeshTool::create_VAO(*mesh->data);

        material = sgl::ShaderMaterial::load_from_file("shaders/2.vs", "shaders/2.fs");

        sgl::DrawCall::DrawArrays arrays;
        arrays.mode = sgl::DrawCall::TRIANGLE_FAN;
        arrays.count = 4;
        mesh->steps->draw_calls.push_back(arrays);

        texture = sgl::Texture2D::load_from_file("textures/sky.png");
        texture->bind();
    }
};

class Window : public sgl::Window
{
private:
    sgl::Ref<Rect> rect;

protected:
    void _initialize() override
    {
        rect = std::make_shared<Rect>();
    }

    void _draw() override
    {
        glClear(GL_COLOR_BUFFER_BIT);
        rect->request_draw();
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
