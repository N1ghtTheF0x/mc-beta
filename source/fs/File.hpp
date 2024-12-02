#ifndef __MINECRAFT_FS_FILE_HPP
#define __MINECRAFT_FS_FILE_HPP

#include <filesystem>
#include <string>
#include "../opengl/Texture.hpp"

namespace Minecraft::FileSystem
{
    std::string readFile(std::filesystem::path path);
    OpenGL::TexturePtr readTexture(std::filesystem::path path);
}

#endif