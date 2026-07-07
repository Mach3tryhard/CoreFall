#ifndef COREFALL_MATERIAL_H
#define COREFALL_MATERIAL_H
#include <glad/glad.h>

#define FOURCC_DXT1 0x31545844 // "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // "DXT5" in ASCII

#ifndef GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
#define GL_COMPRESSED_RGB_S3TC_DXT1_EXT  0x83F0
#define GL_COMPRESSED_RGBA_S3TC_DXT1_EXT 0x83F1
#define GL_COMPRESSED_RGBA_S3TC_DXT3_EXT 0x83F2
#define GL_COMPRESSED_RGBA_S3TC_DXT5_EXT 0x83F3
#endif

class Material {
private:
    GLuint programID;
    GLuint textureID;
public:
    Material(GLuint shaderProgram, const char* texturePath);
    ~Material();

    GLuint loadDDS(const char* imagepath);
    Material(const Material&) = delete;
    Material& operator=(const Material&) = delete;

    void Bind() const;

    GLuint getProgramID() const;
};

#endif //COREFALL_MATERIAL_H