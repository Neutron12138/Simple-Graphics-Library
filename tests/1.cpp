#include <iostream>
#include <cstdlib>
#include <array>
#include "../src/SGL.hpp"

struct TriangleData
{
    const std::vector<glm::vec3> vertices = {
        glm::vec3(0.0f, 0.5f, 0.0f),
        glm::vec3(-0.5f, -0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.0f),
    };

    sgl::Ref<sgl::Program> program;
    sgl::Ref<sgl::Shader> vshader;
    sgl::Ref<sgl::Shader> fshader;
    sgl::Ref<sgl::MeshData> mesh;
    sgl::Ref<sgl::MeshVAO> vao;
    sgl::Ref<sgl::UniformValueVec3> color;
    sgl::Ref<sgl::UniformValueMat4> model;

    TriangleData()
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

        color = std::make_shared<sgl::UniformValueVec3>(program, "color");
        model = std::make_shared<sgl::UniformValueMat4>(program, "model");
    }
};

class Triangle : public sgl::Visual, public sgl::Transform3D
{
private:
    sgl::Ref<TriangleData> data;
    glm::vec3 color;

public:
    Triangle(const sgl::Ref<TriangleData> &dt,
             const glm::vec3 &col,
             const sgl::Transform3D &trans) : data(dt),
                                              color(col),
                                              sgl::Transform3D(trans) {}

protected:
    void _draw(DrawMode draw_mode)
    {
        data->color->value = color;
        data->color->update();

        data->model->value = matrix;
        data->model->update();

        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};

class Window : public sgl::Window
{
private:
    sgl::Ref<sgl::Debugger> debugger;
    std::array<sgl::Ref<Triangle>, 4> triangles;
    sgl::Ref<TriangleData> data;

protected:
    void _initialize() override
    {
        srand(time(nullptr));
        debugger = std::make_shared<sgl::Debugger>();

        data = std::make_shared<TriangleData>();

        for (sgl::SizeT i = 0; i < 4; i++)
            triangles[i] = std::make_shared<Triangle>(data, randvec(0.0, 1.0), randtrans());
    }

    void _draw() override
    {
        glClear(GL_COLOR_BUFFER_BIT);
        for (sgl::SizeT i = 0; i < 4; i++)
            triangles[i]->request_draw();
    }

public:
    float randf(float min, float max, float ratio = 1000)
    {
        int mi = min * ratio;
        int ma = max * ratio;
        int result = rand() % (ma - mi) + mi;
        return result / ratio;
    }

    glm::vec3 randvec(float min, float max, float ratio = 1000)
    {
        glm::vec3 result = {};
        result.x = randf(min, max, ratio);
        result.y = randf(min, max, ratio);
        result.z = randf(min, max, ratio);
        return result;
    }

    sgl::Transform3D randtrans(float ratio = 1000)
    {
        sgl::Transform3D result;
        result.position = randvec(-1.0, 1.0, ratio);
        result.rotation = randvec(-1.0, 1.0, ratio);
        result.scale = randvec(0.0, 1.0, ratio);
        result.update();
        return result;
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
    }

    return 0;
}