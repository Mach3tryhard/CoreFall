#ifndef COREFALL_SPHERE_H
#define COREFALL_SPHERE_H

#include <glad/glad.h>
#include "Mesh.h"

class Sphere : public Mesh {
public:
    Sphere(GLuint shaderProgram, int sectors = 36, int stacks = 18);
};

#endif //COREFALL_SPHERE_H
