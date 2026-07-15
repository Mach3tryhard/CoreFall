#ifndef COREFALL_ICOSAHEDRON_H
#define COREFALL_ICOSAHEDRON_H
#include <glad/glad.h>
#include "Mesh.h"

class Icosahedron: public Mesh{
public:
    Icosahedron(std::shared_ptr<Material> mat);
};

#endif //COREFALL_ICOSAHEDRON_H
