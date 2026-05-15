#version 330 core   
// shader code version

// NOTE: The "in" part is not required. It's convention.
// You could also use "a" for "attribute".

layout(location = 0) in vec3 in_position;    // input position
layout(location = 1) in vec3 in_color;       // input color

out vec3 v_color;

void main()
{
    gl_Position = vec4(in_position, 1);
    gl_Position.xyz *= 0.5;
    v_color = in_color;
}
