#ifndef COREFALL_SQUARE_H
#define COREFALL_SQUARE_H

#include <glad/glad.h>
#include "Mesh.h"
#include <memory>

class Square : public Mesh {
public:
    Square(std::shared_ptr<Material> mat);
};

#endif