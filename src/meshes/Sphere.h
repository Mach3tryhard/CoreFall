#ifndef COREFALL_SPHERE_H
#define COREFALL_SPHERE_H
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Mesh.h"

class Sphere : public Mesh {
public:
    Sphere(std::shared_ptr<Material> mat, int sectors = 36, int stacks = 18);
};

#endif //COREFALL_SPHERE_H
