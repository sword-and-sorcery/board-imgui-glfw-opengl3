
#include "draw_glfw_opengl3.h"

#include "imgui.h"
#include "tileset_glfw/textures.h"
#include <math.h>


static inline ImVec2 operator+(const ImVec2& lhs, const ImVec2& rhs)
{
    return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y);
}
static inline ImVec2 ImRotate(const ImVec2& v, float cos_a, float sin_a)
{
    return ImVec2(v.x * cos_a - v.y * sin_a, v.x * sin_a + v.y * cos_a);
}
void ImageRotated(ImTextureID tex_id, ImVec2 center, ImVec2 size, float angle)
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float cos_a = cosf(angle);
    float sin_a = sinf(angle);
    ImVec2 pos[4] =
            {
                    center + ImRotate(ImVec2(-size.x * 0.5f, -size.y * 0.5f), cos_a, sin_a),
                    center + ImRotate(ImVec2(+size.x * 0.5f, -size.y * 0.5f), cos_a, sin_a),
                    center + ImRotate(ImVec2(+size.x * 0.5f, +size.y * 0.5f), cos_a, sin_a),
                    center + ImRotate(ImVec2(-size.x * 0.5f, +size.y * 0.5f), cos_a, sin_a)
            };
    ImVec2 uvs[4] =
            {
                    ImVec2(0.0f, 0.0f),
                    ImVec2(1.0f, 0.0f),
                    ImVec2(1.0f, 1.0f),
                    ImVec2(0.0f, 1.0f)
            };

    draw_list->AddImageQuad(tex_id, pos[0], pos[1], pos[2], pos[3], uvs[0], uvs[1], uvs[2], uvs[3], IM_COL32_WHITE);
}


void Draw::draw(const std::string& tileset, const std::string& tile, const tile_position& position) {
    float units_value = units.at(tileset);
    ImGui::SetCursorPos(ImVec2(position.x*units_value, position.y*units_value));

    int width, height;
    ImTextureID img = opengl::get_texture(tileset, tile, width, height);

    if (position.rotation == 0) {
        ImGui::Image(img, ImVec2(width, height));
    }
    else {
        ImVec2 p = ImGui::GetCursorScreenPos();
        float radians = position.rotation*M_PI/180.f;
        ImageRotated(img, ImVec2(p.x + width/2.f, p.y + height/2.f), ImVec2(width, height), radians);
    }
}
