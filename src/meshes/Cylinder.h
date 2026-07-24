#ifndef COREFALL_CYLINDER_H
#define COREFALL_CYLINDER_H

#include "Mesh.h"

class Cylinder : public Mesh {
public:
    Cylinder(std::shared_ptr<Material> mat, float radius = 1.0f, float height = 2.0f, int sectors = 72);
};

#endif