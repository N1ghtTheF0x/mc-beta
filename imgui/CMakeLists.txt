add_library(imgui STATIC
    imconfig.h
    imgui_draw.cpp
    imgui_impl_sdl2.cpp
    imgui_impl_sdl2.h
    imgui_internal.h
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui.cpp
    imgui.h
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    imgui_impl_opengl3.cpp
    imgui_impl_opengl3.h
    imgui_impl_opengl3_loader.h
)
target_include_directories(imgui PRIVATE ../sdl2/include)