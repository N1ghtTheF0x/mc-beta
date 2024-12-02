#include "AssetManager.hpp"
#include "../fs/File.hpp"

#ifdef _DEBUG
    #include <imgui.h>
#endif

static std::string TypeStr[] = {
    "Unknown",
    "Texture",
    "Mesh"
};

namespace Minecraft
{
    Identifier::Identifier(const std::string group,const std::string name): mGroup(group), mName(name)
    {

    }
    Identifier::operator const std::string() const
    {
        return full();
    }
    const std::string Identifier::group() const
    {
        return mGroup;
    }
    const std::string Identifier::name() const
    {
        return mName;
    }
    const std::string Identifier::full() const
    {
        return mGroup + ':' + mName;
    }
    AssetManager::AssetManager(): mAssets()
    {

    }
    AssetManager::~AssetManager()
    {
        unload();
    }
#define ADD_ASSET_IMPL(clazz,name) \
    clazz##Ptr& AssetManager::add##name(const Identifier& id,const clazz##Ptr& item) \
    { \
        mAssets.insert_or_assign(id.full(),(const AssetPtr&)item); \
        return (clazz##Ptr&)mAssets.at(id); \
    } \
    clazz##Ptr& AssetManager::add##name(const Identifier& id,clazz##Ptr&& item) \
    { \
        mAssets.insert_or_assign(id.full(),(AssetPtr&&)item); \
        return (clazz##Ptr&)mAssets.at(id); \
    } \
    clazz##Ptr& AssetManager::add##name(const Identifier& id,const clazz& item) \
    { \
        clazz##Ptr ptr = MAKE_ASSET(clazz,item); \
        return add##name(id,ptr); \
    } \
    clazz##Ptr& AssetManager::add##name(const Identifier& id,clazz&& item) \
    { \
        clazz##Ptr ptr = MAKE_ASSET(clazz,item); \
        return add##name(id,ptr); \
    }
#define GET_ASSET_IMPL(clazz,name) \
    clazz##Ptr& AssetManager::get##name(const Identifier& id) {return get##name(id.full());} \
    const clazz##Ptr& AssetManager::get##name(const Identifier& id) const {return get##name(id.full());} \
    clazz##Ptr& AssetManager::get##name(const std::string id) {return (clazz##Ptr&)mAssets.at(id);} \
    const clazz##Ptr& AssetManager::get##name(const std::string id) const {return (clazz##Ptr&)mAssets.at(id);}
    ADD_ASSET_IMPL(OpenGL::Texture,Texture)
    GET_ASSET_IMPL(OpenGL::Texture,Texture)
    ADD_ASSET_IMPL(OpenGL::Mesh,Mesh)
    GET_ASSET_IMPL(OpenGL::Mesh,Mesh)
    OpenGL::TexturePtr& AssetManager::addTexture(const Identifier& id,std::filesystem::path path)
    {
        OpenGL::TexturePtr ptr = FileSystem::readTexture(path);
        return addTexture(id,ptr);
    }
    void AssetManager::load()
    {
        for(auto &asset : mAssets)
            asset.second->load();
    }
    void AssetManager::unload()
    {
        for(auto &asset : mAssets)
            asset.second->unload();
    }
    static const char* wate_what(Asset::Type expected,Asset::Type got)
    {
        std::string str = "expected ";
        str
        .append(TypeStr[(unsigned char)expected])
        .append(" got ")
        .append(TypeStr[(unsigned char)got])
        .append(" instead");
        const char* v = str.c_str();
        return v;
    }
#ifdef _DEBUG
    void AssetManager::Editor(AssetManager& assets,const char* name,bool* enabled)
    {
        ImGui::Begin(name,enabled);
        for(auto &asset : assets.mAssets)
        {
            std::string name = asset.first + " (";
            name.append(TypeStr[(unsigned char)asset.second->type()]);
            name.push_back(')');
            if(ImGui::TreeNode(name.c_str()))
            {
                switch(asset.second->type())
                {
                    case Asset::Type::Texture:
                    {
                        OpenGL::Texture::EditorContent((OpenGL::TexturePtr&)asset.second);
                        break;
                    }
                    case Asset::Type::Mesh:
                    {
                        OpenGL::Mesh::EditorContent((OpenGL::MeshPtr&)asset.second);
                        break;
                    }
                    default:
                        ImGui::Text("Unknown asset type '%s'",asset.second->type());
                        break;
                }
                ImGui::TreePop();
            }
        }
        ImGui::End();
    }
#endif
    WrongAssetTypeException::WrongAssetTypeException(Asset::Type expected,Asset::Type got): std::exception(wate_what(expected,got))
    {
        
    }
}