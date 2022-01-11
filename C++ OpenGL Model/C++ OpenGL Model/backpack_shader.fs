#version 330 core

out vec3 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main() {
  FragColor = texture(texture_diffuse1, TexCoords);
}
