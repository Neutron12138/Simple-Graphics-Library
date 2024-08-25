#version 460 core

out vec4 o_color;

uniform vec3 color;

void main()
{
    o_color = vec4(color, 1.0);
}
