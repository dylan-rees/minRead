#version 450

layout(location = 0) in vec2 vertex_position;

uniform mat4 matrix;

void main()
{
        gl_Position = matrix*vec4(vertex_position, 0.0f, 1.0f);
        gl_PointSize = 3.0f;
}
