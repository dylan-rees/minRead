#version 450

layout(location = 0) in float vertex_position;

uniform mat4 matrix;

void main()
{
        gl_Position = matrix*vec4(vertex_position, 0.0f, 0.0f, 1.0f);
        gl_PointSize = 5.0f;
}
