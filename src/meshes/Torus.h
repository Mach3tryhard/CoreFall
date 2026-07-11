#ifndef COREFALL_TORUS_H
#define COREFALL_TORUS_H
#include <glad/glad.h>
#include "Mesh.h"

class Torus : public Mesh {
public:
    Torus(std::shared_ptr<Material> mat, float mainRadius = 1.0f, float tubeRadius = 0.3f, int mainSectors = 36, int tubeSectors = 18);
};

#endif //COREFALL_TORUS_H