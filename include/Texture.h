#pragma once

class Texture
{
public:
    unsigned int ID;

    Texture(const char* texPath, bool flip);

    void UseTexture(int textureUnit, int textureID);
};

