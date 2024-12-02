#ifndef __MINECRAFTT_ASSETS_ASSET_HPP
#define __MINECRAFTT_ASSETS_ASSET_HPP

#include <memory>
#include <map>
#include <string>

namespace Minecraft
{
    class Asset
    {
    public:
        enum struct Type : unsigned char
        {
            Unknown,
            Texture,
            Mesh
        };
        virtual void load() {}
        virtual void unload() {}
        virtual Type type() const = 0;
    };
    #define DECLARE_ASSET(clazz) class clazz; typedef std::shared_ptr<clazz> clazz##Ptr;
    DECLARE_ASSET(Asset)
    #define MAKE_ASSET(clazz,...) std::make_shared<clazz>(__VA_ARGS__)
    class Identifier
    {
    private:
        const std::string mGroup;
        const std::string mName;
    public:
        Identifier(const std::string group,const std::string name);
        operator const std::string() const;
        const std::string group() const;
        const std::string name() const;
        const std::string full() const;
    };
    typedef std::map<const std::string,AssetPtr> Assets;
}

#endif