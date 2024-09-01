#ifndef TRANSFORM3D_HPP
#define TRANSFORM3D_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../system/math.hpp"

namespace sgl
{
    class Transform3D
    {
    public:
        glm::mat4 matrix = IDENTITY_MATRIX;

        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 rotation = glm::vec3(0.0f);
        glm::vec3 scale = glm::vec3(1.0f);

    public:
        Transform3D(const glm::vec3 &pos = glm::vec3(0.0f),
                    const glm::vec3 &rot = glm::vec3(0.0f),
                    const glm::vec3 &sca = glm::vec3(1.0f)) : position(pos),
                                                              rotation(rot),
                                                              scale(sca)
        {
            update();
        }

    public:
        virtual void update()
        {
            matrix = glm::scale(IDENTITY_MATRIX, scale);
            matrix = glm::translate(matrix, position);
            matrix = glm::rotate(matrix, rotation.x, POSITIVE_X);
            matrix = glm::rotate(matrix, rotation.y, POSITIVE_Y);
            matrix = glm::rotate(matrix, rotation.z, POSITIVE_Z);
        }
    };

} // namespace sgl

#endif
