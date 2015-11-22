#pragma once
#include "gl/glew.h"

#include "Camera.h"
#include "Shaders.h"
#include "glm/gtc/type_ptr.hpp"

#define TEXTURE_SIZE 64

class SkyBox
{
public:
    SkyBox(char* texturePath);
    ~SkyBox();
    void render(Camera *camera, glm::mat4 projection); 
    void SkyBox::reload();
private:
    Shaders shaders;
    GLuint texName; 
    GLuint vbo; 
    GLuint vao;

};