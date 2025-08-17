#version 330 core
layout (location = 0) in vec2 aPos;

uniform float offset_x;
uniform float offset_y;
uniform float scale_x;
uniform float scale_y;

void main()
{
    float x = aPos.x * scale_x + offset_x;
    float y = aPos.y * scale_y + offset_y;
    gl_Position = vec4(x, y, 0.0, 1.0);
}
