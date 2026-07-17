#ifndef COREFALL_TORUS_H
#define COREFALL_TORUS_H
#include <glad/glad.h>
#include "Mesh.h"
#include <glm/glm.hpp>

class Torus : public Mesh {
public:
    Torus(std::shared_ptr<Material> mat, float mainRadius = 1.0f, float tubeRadius = 0.3f, int mainSectors = 128, int tubeSectors = 64);
};

#endif //COREFALL_TORUS_H