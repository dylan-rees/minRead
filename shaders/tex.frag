#version 450

out vec4 frag_color;

void main()
{
    vec2 coord = gl_PointCoord - vec2(0.5);  //from [0,1] to [-0.5,0.5]
    if(length(coord) > 0.7075)                  //outside of circle radius?
        discard;

    frag_color = vec4 (1.0f, 0.0f, 0.0f, 1.0);
}
