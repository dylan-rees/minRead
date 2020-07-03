#version 450

in float col;
uniform sampler1D cat_texture;
out vec4 frag_color;

void main()
{
	float colorI = float(col/11.0f);
	vec4 tex_col = texture (cat_texture, colorI);
	frag_color = tex_col;//vec4 (color_out, 1.0);
}