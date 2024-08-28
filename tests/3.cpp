#include <iostream>
#include "../src/SGL.hpp"

class Rect : public sgl::PrimitiveMeshInstance
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
    sgl::Ref<sgl::MeshData> data;
    sgl::Ref<sgl::Texture2D> texture;

public:
    Rect()
    {
        data = std::make_shared<sgl::MeshData>();
        data->vertices = vertices;
        data->texCoords = texCoords;

        material = sgl::ShaderMaterial::load_from_file("shaders/2.vs", "shaders/2.fs");
        vao = sgl::MeshTool::create_VAO(*data);

        sgl::DrawStep::DrawArrays arrays;
        arrays.mode = sgl::DrawStep::TRIANGLE_FAN;
        arrays.count = 4;
        draw_step = std::make_shared<sgl::DrawStep>(arrays);

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
