#version 330 core

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  sampler2D emission;
  float shininess;
};

struct Light {
  vec3 position;
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float constant;
  float linear;
  float quadratic;
  float cutOff;
};

out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;

uniform vec3 viewPos;

uniform Material material;
uniform Light light;

void main() {
  vec3 lightDir = normalize(light.position - FragPos);
  float theta = dot(lightDir, normalize(-light.direction));

  vec3 result;
  if (theta > light.cutOff) {
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
    vec3 specularMap = vec3(texture(material.specular, TexCoords));
    vec3 specular = light.specular * spec * specularMap;

    vec3 emissionMask = floor(vec3(1.0f) - specularMap);
    vec3 emission = vec3(texture(material.emission, TexCoords)) * emissionMask;

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance);
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    result = ambient + diffuse + specular + emission;
  } else {
    result = light.ambient * vec3(texture(material.diffuse, TexCoords));
  }
  
  FragColor = vec4(result, 1.0f);
}
