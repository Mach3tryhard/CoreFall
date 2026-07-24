#ifndef COREFALL_TRAPEZOHEDRON_H
#define COREFALL_TRAPEZOHEDRON_H

#include "Mesh.h"

class Trapezohedron : public Mesh {
public:
    Trapezohedron(std::shared_ptr<Material> mat, float radius = 1.0f, float height = 1.0f);
};

#endif