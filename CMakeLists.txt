cmake_minimum_required(VERSION 3.22)

project(Minecraft VERSION 1.7.3)

# properties

set(MINECRAFT_VERSION "b1.7.3")

# c++ settings

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# folders

set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)
set(DATA_DIR ${BIN_DIR}/data)
set(SHADERS_DIR ${CMAKE_SOURCE_DIR}/shaders)

# redirect output

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LIB_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LIB_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${BIN_DIR})
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)

# thirdparty

add_subdirectory(glad)
add_subdirectory(sdl2)
add_subdirectory(imgui)
add_subdirectory(glm)

# find

find_package(OpenGL REQUIRED)

# git

execute_process(
    COMMAND git log -1 --format=%h
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
    OUTPUT_VARIABLE GIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# configure

configure_file(MinecraftConfig.hpp.in gen/MinecraftConfig.hpp)

# executable

add_executable(Minecraft main.cpp
    source/Instance.hpp
    source/instance.cpp
    source/Client.hpp
    source/client.cpp

    source/window.cpp
    source/Window.hpp

    source/input.cpp
    source/Input.hpp

    source/opengl/OpenGL.hpp
    source/opengl/Shader.hpp
    source/opengl/shader.cpp
    source/opengl/Mesh.hpp
    source/opengl/mesh.cpp
    source/opengl/Texture.hpp
    source/opengl/texture.cpp

    source/fs/File.hpp
    source/fs/file.cpp

    source/math/Camera.hpp
    source/math/camera.cpp
    source/math/Color.hpp
    source/math/math.cpp

    source/interfaces/IEditable.hpp
    source/interfaces/IMesh.hpp
    source/interfaces/IRenderer.hpp
    source/interfaces/IShader.hpp
    source/interfaces/ITexture.hpp

    source/assets/Asset.hpp
    source/assets/AssetManager.hpp
    source/assets/assetman.cpp
)
target_link_libraries(Minecraft PRIVATE glad imgui SDL2 SDL2main ${OPENGL_LIBRARIES} glm)
target_include_directories(Minecraft PRIVATE imgui glad/include sdl2/include build/gen include ${OPENGL_INCLUDE_DIRS} glm)
if(WIN32)
    target_sources(Minecraft PRIVATE win32/icon.rc)
endif()

# copy data

file(MAKE_DIRECTORY ${DATA_DIR})
file(COPY ${SHADERS_DIR} DESTINATION ${DATA_DIR})