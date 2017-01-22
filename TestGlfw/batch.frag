#version 330 core

in vec2 TexCoord;
in vec4 color;
out vec4 frag_color;

uniform sampler2D image;
//uniform vec3 spriteColor;

void main()
{
    frag_color = texture(image, TexCoord) * color;
    //color = vec4(1.0, 0.0, 0.0, 1.0);
}