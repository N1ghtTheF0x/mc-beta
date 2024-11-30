#ifndef __MINECRAFT_INSTANCE_HPP
#define __MINECRAFT_INSTANCE_HPP

#include <vector>
#include <string>

namespace Minecraft
{
    typedef std::vector<std::string> Arguments;
    class Instance
    {
    protected:
        Arguments mArgs;
        Instance(int argc,char* argv[]);
    public:
        Instance(const Instance&) = delete;
        Instance& operator=(const Instance&) = delete;
    };
}

#endif