#ifndef COREFALL_LOADED_H
#define COREFALL_LOADED_H
#include <vector>
#include "Mesh.h"

class Loaded: public Mesh {
public:
    Loaded(std::shared_ptr<Material> mat);
    bool loadOBJ(const char * path);
};

#endif