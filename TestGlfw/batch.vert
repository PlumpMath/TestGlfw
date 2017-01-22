#version 330 core
layout (location = 0) in vec4 vertex;  // <vec2 pos, vec2 tex>
layout (location = 1) in vec4 in_color;

out vec2 TexCoord;
out vec4 color;

uniform mat4 projection;

void main()
{
	color = in_color;
    TexCoord = vertex.zw;
    gl_Position = projection * vec4(vertex.xy, 0.0f, 1.0f);    
}