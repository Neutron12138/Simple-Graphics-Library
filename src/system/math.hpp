#ifndef MATH_HPP
#define MATH_HPP

#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include "../base/type.hpp"

namespace sgl
{
    const glm::vec3 POSITIVE_X = glm::vec3(1.0f, 0.0f, 0.0f);
    const glm::vec3 NEGATIVE_X = -POSITIVE_X;

    const glm::vec3 POSITIVE_Y = glm::vec3(0.0f, 1.0f, 0.0f);
    const glm::vec3 NEGATIVE_Y = -POSITIVE_Y;

    const glm::vec3 POSITIVE_Z = glm::vec3(0.0f, 0.0f, 1.0f);
    const glm::vec3 NEGATIVE_Z = -POSITIVE_Z;

    const glm::mat4 IDENTITY_MATRIX = glm::mat4(1.0f);

    class Math
    {
    public:
        static constexpr Float64 E = M_E;
        static constexpr Float64 PI = M_PI;
        static constexpr Float64 TAU = 2.0 * PI;

        static glm::vec3 calc_euler_angle(Float64 yaw, Float64 pitch)
        {
            Float64 y = std::sin(pitch);
            Float64 h = std::cos(pitch);
            Float64 x = -std::sin(yaw) * h;
            Float64 z = -std::cos(yaw) * h;
            return glm::vec3(x, y, z);
        }

        template <typename T>
        static T cos(const glm::detail::tvec2<T> &a, const glm::detail::tvec2<T> &b)
        {
            return glm::dot(glm::normalize(a), glm::normalize(b));
        }

        template <typename T>
        static T cos(const glm::detail::tvec3<T> &a, const glm::detail::tvec3<T> &b)
        {
            return glm::dot(glm::normalize(a), glm::normalize(b));
        }

        template <typename T>
        static T cos(const glm::detail::tvec4<T> &a, const glm::detail::tvec4<T> &b)
        {
            return glm::dot(glm::normalize(a), glm::normalize(b));
        }

        template <typename T>
        static T get_projection_length(const glm::detail::tvec2<T> &from,
                                       const glm::detail::tvec2<T> &to)
        {
            return glm::length(from) * cos(from, to);
        }

        template <typename T>
        static T get_projection_length(const glm::detail::tvec3<T> &from,
                                       const glm::detail::tvec3<T> &to)
        {
            return glm::length(from) * cos(from, to);
        }

        template <typename T>
        static T get_projection_length(const glm::detail::tvec4<T> &from,
                                       const glm::detail::tvec4<T> &to)
        {
            return glm::length(from) * cos(from, to);
        }

        template <typename T>
        static glm::detail::tvec2<T> project(const glm::detail::tvec2<T> &from,
                                             const glm::detail::tvec2<T> &to)
        {
            return get_projection_length(from, to) * to;
        }

        template <typename T>
        static glm::detail::tvec3<T> project(const glm::detail::tvec3<T> &from,
                                             const glm::detail::tvec3<T> &to)
        {
            return get_projection_length(from, to) * to;
        }

        template <typename T>
        static glm::detail::tvec4<T> project(const glm::detail::tvec4<T> &from,
                                             const glm::detail::tvec4<T> &to)
        {
            return get_projection_length(from, to) * to;
        }
    };

    class Coordinate
    {
    public:
        glm::vec3 x = POSITIVE_X;
        glm::vec3 y = POSITIVE_Y;
        glm::vec3 z = POSITIVE_Z;

    public:
        Coordinate() {}
        Coordinate(const glm::vec3 &ax, const glm::vec3 &ay, const glm::vec3 &az = POSITIVE_Z)
            : x(ax), y(ay), z(az) {}

    public:
        glm::vec3 get_position(const glm::vec2 &coord)
        {
            return coord.x * x + coord.y * y;
        }

        glm::vec3 get_position(const glm::vec3 &coord)
        {
            return coord.x * x + coord.y * y + coord.z * z;
        }

        glm::vec3 get_coordinate(const glm::vec3 &vec)
        {
            glm::vec3 coord = {};
            coord.x = Math::get_projection_length(vec, x);
            coord.y = Math::get_projection_length(vec, y);
            coord.z = Math::get_projection_length(vec, z);
            return coord;
        }
    };

} // namespace sgl

namespace std
{
    template <typename T>
    ostream &operator<<(ostream &os, const glm::detail::tvec2<T> &vec)
    {
        os << "(" << vec.x << ", "
           << vec.y << ")";
        return os;
    }

    template <typename T>
    ostream &operator<<(ostream &os, const glm::detail::tvec3<T> &vec)
    {
        os << "(" << vec.x << ", "
           << vec.y << ", "
           << vec.z << ")";
        return os;
    }

    template <typename T>
    ostream &operator<<(ostream &os, const glm::detail::tvec4<T> &vec)
    {
        os << "(" << vec.x << ", "
           << vec.y << ", "
           << vec.z << ", "
           << vec.w << ")";
        return os;
    }

    ostream &operator<<(ostream &os, const sgl::Coordinate &coord)
    {
        os << "(" << coord.x << ", "
           << coord.y << ", "
           << coord.z << ")";
        return os;
    }

} // namespace std

#endif
