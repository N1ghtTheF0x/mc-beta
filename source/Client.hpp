#ifndef __MINECRAFT_CLIENT_HPP
#define __MINECRAFT_CLIENT_HPP

#include "Instance.hpp"

namespace Minecraft
{
    class Client : public Instance
    {
    private:
        float mDeltaTime = 0.0f;
        bool mRunning = true;
        void loop();
        void event();
        void update();
        void draw();
        void cleanup();
    public:
        Client(int argc,char* argv[]);
        Client(const Client&) = delete;
        Client& operator=(const Client&) = delete;
        ~Client();

        void init();
    };
}

#endif