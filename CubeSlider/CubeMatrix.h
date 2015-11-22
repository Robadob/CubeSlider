#pragma once

#define NO_CUBE 0
#define STATIC_CUBE -1
//#include "Cube.h"
#include <map>
#include <glm/glm.hpp>

#include "Entity.h"

struct Cube
{
public :
    glm::vec3 colour;
};
class CubeMatrix
{
public:
    CubeMatrix(int diameter=4);
    ~CubeMatrix();

    void render();

private:

    int encodeHash(glm::ivec3 location);
    glm::ivec3 decodeHash(int hash);

    int diameter;
    Entity cubeModel;
    int ***cubes;
    std::map<int, Cube> cubeMap;
};

