#include "Material.h"
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Material::Material(GLuint shaderProgram, const char* texturePath) {
    programID = shaderProgram;

    std::string pathStr = texturePath;
    if (pathStr.length() >= 4 && pathStr.substr(pathStr.length() - 4) == ".dds") {
        textureID = loadDDS(texturePath);
    } else {
        textureID = loadStandardImage(texturePath);
    }
}

Material::~Material() {
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
    }
}

void Material::Bind() const {
    glUseProgram(programID);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    GLuint textureLocation = glGetUniformLocation(programID, "myTextureSampler");
    glUniform1i(textureLocation, 0);
}

GLuint Material::getProgramID() const {
    return programID;
}

GLuint Material::loadStandardImage(const char * imagepath) {
    GLuint newTextureID;
    glGenTextures(1, &newTextureID);
    glBindTexture(GL_TEXTURE_2D, newTextureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(imagepath, &width, &height, &nrChannels, 0);

    if (data) {
        GLenum format = GL_RGB;
        if (nrChannels == 1) format = GL_RED;
        else if (nrChannels == 3) format = GL_RGB;
        else if (nrChannels == 4) format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data);
    return newTextureID;
}

GLuint Material::loadDDS(const char * imagepath) {
    unsigned char header[124];
    FILE *fp;

    fp = fopen(imagepath, "rb");
    if (fp == NULL) {
        return 0;
    }

    char filecode[4];
    fread(filecode, 1, 4, fp);
    if (strncmp(filecode, "DDS ", 4) != 0) {
        fclose(fp);
        return 0;
    }

    fread(&header, 124, 1, fp);

    unsigned int height      = *(unsigned int*)&(header[8 ]);
    unsigned int width       = *(unsigned int*)&(header[12]);
    unsigned int linearSize  = *(unsigned int*)&(header[16]);
    unsigned int mipMapCount = *(unsigned int*)&(header[24]);
    unsigned int fourCC      = *(unsigned int*)&(header[80]);

    unsigned char * buffer;
    unsigned int bufsize;

    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    fclose(fp);

    unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch(fourCC) {
        case FOURCC_DXT1: format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; break;
        case FOURCC_DXT3: format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; break;
        case FOURCC_DXT5: format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; break;
        default: free(buffer); return 0;
    }

    GLuint newTextureID;
    glGenTextures(1, &newTextureID);
    glBindTexture(GL_TEXTURE_2D, newTextureID);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level) {
        unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

        offset += size;
        width  /= 2;
        height /= 2;
    }

    free(buffer);
    return newTextureID;
}