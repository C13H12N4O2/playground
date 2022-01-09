#version 330 core

struct Material {
  sampler2D diffuse;
  vec3 specular;
  float shininess;
};

struct Light {
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform Material material;
uniform Light light;

void main() {
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(norm, lightDir), 0.0f);
  vec3 diffuse = light.diffuse * vec3(texture(material.diffuse, TexCoords));
  
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
  vec3 specular = light.specular * (spec * material.specular);
  
  vec3 result = ambient + diffuse + specular;
  FragColor = vec4(result, 1.0f);
}
