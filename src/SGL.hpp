#ifndef SGL_HPP
#define SGL_HPP

#define STB_IMAGE_IMPLEMENTATION

#include "base/type.hpp"
#include "base/noncopyable.hpp"
#include "base/ref.hpp"

#include "system/string.hpp"
#include "system/time.hpp"
#include "system/window.hpp"
#include "system/image.hpp"

#include "gl/debugger.hpp"
#include "gl/shader.hpp"
#include "gl/program.hpp"
#include "gl/buffer.hpp"
#include "gl/vertex_array.hpp"
#include "gl/uniform.hpp"
#include "gl/texture.hpp"
#include "gl/texture2d.hpp"
#include "gl/frame_buffer.hpp"

#include "shader/material.hpp"
#include "shader/shader_material.hpp"
#include "shader/standard_material.hpp"
#include "shader/shader_generator.hpp"

#include "mesh/mesh.hpp"
#include "mesh/mesh_tool.hpp"
#include "mesh/mesh_generator.hpp"
#include "mesh/mesh_instance.hpp"

#include "visual/visual.hpp"
#include "visual/draw_step.hpp"
#include "visual/transform3d.hpp"

#include "environment/environment.hpp"
#include "environment/light.hpp"
#include "environment/sky.hpp"

#endif
