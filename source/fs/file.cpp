#include "File.hpp"
#include <fstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Minecraft
{
    std::string FileSystem::readFile(std::filesystem::path path)
    {
        if(!std::filesystem::is_regular_file(path))
            return "";
        std::string str;
        std::ifstream file(path,std::ios::binary);
        uintmax_t size = std::filesystem::file_size(path);
        std::cout << "reading file: " << std::filesystem::absolute(path) << std::endl;
        for(uintmax_t i = 0;i < size;i++)
        {
            std::string::value_type letter;
            file.read(&letter,sizeof(letter));
            str.push_back(letter);
        }
        return str;
    }
    OpenGL::TexturePtr FileSystem::readTexture(std::filesystem::path path)
    {
        OpenGL::TextureData d;
        std::string p = path.string();
        int width, height, channels;
        std::cout << "reading texture: " << std::filesystem::absolute(path) << std::endl;
        unsigned char* data = stbi_load(p.c_str(),&width,&height,&channels,4);
        size_t pixelSize = 1 + ((width * height) * channels);
        for(size_t i = 0;i < pixelSize;i++)
            d.push_back(data[i]);
        stbi_image_free(data);
        return MAKE_ASSET(OpenGL::Texture,d,width,height,channels);
    }
}