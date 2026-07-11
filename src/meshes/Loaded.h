#ifndef COREFALL_LOADED_H
#define COREFALL_LOADED_H
#include <vector>
#include "Mesh.h"

class Loaded: public Mesh {
private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
public:
    Loaded(std::shared_ptr<Material> mat);
    bool loadOBJ(const char * path);
};


#endif //COREFALL_LOADED_H
