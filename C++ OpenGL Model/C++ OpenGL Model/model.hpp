#pragma once

#include "common.h"
#include "mesh.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int TextureFromFile(const char* path, const std::string &directory, bool gamma = false);

class Model {
public:
  Model(const char* path) {
    loadModel(path);
  }
  
  void Draw(Shader &shader) {
    for (auto mesh : meshes)
      mesh.Draw(shader);
  }
  
private:
  std::vector<Mesh> meshes;
  std::vector<Texture> textures_loaded;
  std::string directory;
  
  void loadModel(std::string path) {
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
      std::cout << "ERROR:ASSIMP::" << import.GetErrorString() << "\n";
      return;
    }
    
    directory = path.substr(0, path.find_last_of('/'));
    
    processNode(scene->mRootNode, scene);
  }
  
  void processNode(aiNode* node, const aiScene* scene) {
    for (size_t i = 0; i != node->mNumMeshes; ++i) {
      aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
      meshes.push_back(processMesh(mesh, scene));
    }
    
    for (size_t i = 0; i != node->mNumChildren; ++i)
      processNode(node->mChildren[i], scene);
  }
  
  Mesh processMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    
    for (size_t i = 0; i != mesh->mNumVertices; ++i) {
      Vertex vertex;
      glm::vec3 vector;
      vector.x = mesh->mVertices[i].x;
      vector.y = mesh->mVertices[i].y;
      vector.z = mesh->mVertices[i].z;
      vertex.Position = vector;
      
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.Normal = vector;
      
      if (mesh->mTextureCoords[0]) {
        glm::vec2 vec;
        vec.x = mesh->mTextureCoords[0][i].x;
        vec.y = mesh->mTextureCoords[0][i].y;
        vertex.TexCoords = vec;
      } else {
        vertex.TexCoords = glm::vec2(0.0f, 0.0f);
      }
      
      vertices.push_back(vertex);
    }
    
    for (size_t i = 0; i != mesh->mNumFaces; ++i) {
      aiFace face = mesh->mFaces[i];
      
      for (size_t j = 0; j != face.mNumIndices; ++i)
        indices.push_back(face.mIndices[j]);
    }
    
    if (mesh->mMaterialIndex >= 0) {
      aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
      std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
      textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
      
      std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
      textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    
    return Mesh(vertices, indices, textures);
  }
  
  std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
    std::vector<Texture> textures;
    
    for (size_t i = 0; i != mat->GetTextureCount(type); ++i) {
      aiString str;
      mat->GetTexture(type, static_cast<unsigned int>(i), &str);
      
      bool skip = false;
      for (size_t j = 0; j != textures_loaded.size(); ++j) {
        if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0) {
          textures.push_back(textures_loaded[j]);
          skip = true;
          break;
        }
      }
      
      if (!skip) {
        Texture texture;
        texture.id = TextureFromFile(str.C_Str(), directory);
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
      }
    }
    
    return textures;
  }
};

unsigned int TextureFromFile(const char* path, const std::string &directory, bool gamma) {
  std::string filename = std::string(path);
  filename = directory + '/' + filename;
  
  unsigned int textureID;
  glGenTextures(1, &textureID);
  
  int width, height, nrComponents;
  unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
  
  if (data) {
    GLenum format;
    switch (nrComponents) {
      case 1:
        format = GL_RED;
        break;
        
      case 3:
        format = GL_RGB;
        break;
        
      case 4:
        format = GL_RGBA;
        break;
        
      default:
        std::cout << "Format failed to load\n";
        break;
    }
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  } else {
      std::cout << "Texture failed to load at path: " << path << '\n';
  }
  
  stbi_image_free(data);
  return textureID;
}
