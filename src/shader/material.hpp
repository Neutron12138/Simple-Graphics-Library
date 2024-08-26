#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "../gl/program.hpp"
#include "../base/ref.hpp"

namespace sgl
{
    class Material
    {
    public:
        virtual ~Material() = default;

    public:
        virtual void begin() = 0;
        virtual void end() = 0;
    };

} // namespace sgl

#endif
