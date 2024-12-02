#ifndef __MINECRAFTT_ASSETS_ASSET_MANAGER_HPP
#define __MINECRAFTT_ASSETS_ASSET_MANAGER_HPP

#include "Asset.hpp"
#include "../opengl/Texture.hpp"
#include "../opengl/Mesh.hpp"

#include <filesystem>
#include <exception>

namespace Minecraft
{
    #define ASSET_ADD_DEF(clazz,name) \
        clazz##Ptr& add##name(const Identifier& id,const clazz##Ptr& item); \
        clazz##Ptr& add##name(const Identifier& id,clazz##Ptr&& item); \
        clazz##Ptr& add##name(const Identifier& id,const clazz& item); \
        clazz##Ptr& add##name(const Identifier& id,clazz&& item); \
        clazz##Ptr& add##name(const Identifier& id,std::filesystem::path path);
    #define ASSET_GET_DEF(clazz,name) \
        clazz##Ptr& get##name(const Identifier& id); \
        const clazz##Ptr& get##name(const Identifier& id) const; \
        clazz##Ptr& get##name(const std::string id); \
        const clazz##Ptr& get##name(const std::string id) const;
    class AssetManager
    {
    private:
        Assets mAssets;
    public:
#ifdef _DEBUG
        static void Editor(AssetManager& assets,const char* name,bool* enabled = (bool*)0);
#endif
        AssetManager();
        ~AssetManager();
        ASSET_ADD_DEF(OpenGL::Texture,Texture)
        ASSET_GET_DEF(OpenGL::Texture,Texture)
        ASSET_ADD_DEF(OpenGL::Mesh,Mesh)
        ASSET_GET_DEF(OpenGL::Mesh,Mesh)
        void load();
        void unload();
    };
    class WrongAssetTypeException : public std::exception
    {
    public:
        WrongAssetTypeException(Asset::Type expected,Asset::Type got);
    };
}

#endif