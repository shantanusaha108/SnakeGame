#version 330 core
out vec4 FragColor;

uniform float ourColor_r;
uniform float ourColor_g;
uniform float ourColor_b;

void main()
{
    FragColor = vec4(ourColor_r, ourColor_g, ourColor_b, 1.0);
}
