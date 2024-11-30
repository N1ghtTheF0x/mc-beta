#include "source/Client.hpp"
#include <iostream>

#ifdef __cplusplus
extern "C"
#endif
int SDL_main(int argc,char* argv[])
{
    Minecraft::Client client(argc,argv);
    client.init();
    return EXIT_SUCCESS;
}