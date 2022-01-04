#pragma once

#include <bgfx/bgfx.h>

#define IMGUI_MBUT_LEFT   0x01
#define IMGUI_MBUT_RIGHT  0x02
#define IMGUI_MBUT_MIDDLE 0x04

namespace bx { struct AllocatorI; }

void ImguiCreate(float fontSize = 18.0f, bx::AllocatorI* allocator = NULL);
void ImguiDestroy();

void ImguiBeginFrame(int32_t mx, int32_t my, uint8_t button, int32_t scroll, uint16_t width, uint16_t height, int input_char = -1, bgfx::ViewId view_id = 255);
void ImguiEndFrame();

namespace ImGui
{
#define IMGUI_FLAGS_NONE        UINT8_C(0x00)
#define IMGUI_FLAGS_ALPHA_BLEND UINT8_C(0x01)
}