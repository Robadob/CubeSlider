#include "CubeMatrix.h"

CubeMatrix::CubeMatrix(int diameter)
    : diameter(diameter)
    , cubeModel("../models/cube.obj")
{
    cubeModel.clearMaterial();
    if (diameter <= 1)
    {
        printf("Diameter must be above 1.");
        exit(1);
    }
    //Init array
    cubes = new int**[diameter];
    for (int x = 0; x < diameter; x++)
    {
        cubes[x] = new int*[diameter];
        for (int y = 0; y < diameter; y++)
            cubes[x][y] = new int[diameter];
    }
    //Init all surface cubes
    for (int x = 0; x < diameter; x++)
        for (int y = 0; y < diameter; y++)
            for (int z = 0; z < diameter; z++)
            {
                if (
                    x == 0 || (x + 1) == diameter ||
                    y == 0 || (y + 1) == diameter ||
                    z == 0 || (z + 1) == diameter
                ){
                    int hash = encodeHash(glm::ivec3(x,y,z));
                    cubes[x][y][z] = hash;
                    cubeMap[hash] = Cube{ glm::vec3(
                        static_cast<float>(x) / (diameter - 1),
                        static_cast<float>(y) / (diameter - 1),
                        static_cast<float>(z) / (diameter - 1)
                        ) };
                }
                else
                {
                    cubes[x][y][z] = STATIC_CUBE;
                }
            }
    cubeMap[-1] = Cube{glm::vec3(0.5f,0.5f,0.5f)};
    //Link id's to cube data in a hashmap
}
CubeMatrix::~CubeMatrix()
{
    //Deinit array
    for (int x = 0; x < diameter; x++)
    {
        for (int y = 0; y < diameter; y++)
            delete[] cubes[x][y];
        delete[] cubes[x];
    }
    delete[] cubes;
}
void CubeMatrix::render()
{
    //For each cube
    for (int x = 0; x < diameter; x++)
    for (int y = 0; y < diameter; y++)
    for (int z = 0; z < diameter; z++)
    {
        if (cubes[x][y][z] == NO_CUBE)
            continue;
        Cube c = cubeMap[cubes[x][y][z]];
        cubeModel.setLocation(glm::vec3(x - (diameter / 2.0), y - (diameter / 2.0), z - (diameter / 2.0)));
        cubeModel.setColor(c.colour);
        cubeModel.render();
    }
}
int CubeMatrix::encodeHash(glm::ivec3 location){
    return (location.x*diameter*diameter) + (location.y*diameter) + location.z;
}
glm::ivec3 CubeMatrix::decodeHash(int hash)
{
    glm::ivec3 rtn;
    rtn.x = hash / (diameter*diameter);
    rtn.y = (hash - (rtn.x *diameter*diameter)) / diameter;
    rtn.z = (hash - (rtn.x *diameter*diameter) - (rtn.y *diameter));
    return rtn;
}