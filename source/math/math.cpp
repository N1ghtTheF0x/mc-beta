#include "Color.hpp"

#ifdef _DEBUG
    #include <imgui.h>
#endif

namespace Minecraft::Math
{
#ifdef _DEBUG
    void Color::EditorContent(Color& color)
    {
        ImGui::ColorEdit4("Value",color.data);
    }
#endif
}