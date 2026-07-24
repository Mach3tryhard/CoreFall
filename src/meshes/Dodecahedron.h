#ifndef COREFALL_DODECAHEDRON_H
#define COREFALL_DODECAHEDRON_H

#include "Mesh.h"

class Dodecahedron : public Mesh {
public:
    Dodecahedron(std::shared_ptr<Material> mat, float radius = 1.0f);
};

#endif