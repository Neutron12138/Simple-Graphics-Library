#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include "../base/noncopyable.hpp"

namespace sgl
{
    class Texture : public NonCopyable
    {
    };

    class Texture2D : public Texture
    {
    };

} // namespace sgl

#endif
