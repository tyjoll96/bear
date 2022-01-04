// Derived from this Gist by Richard Gale:
//     https://gist.github.com/RichardGale/6e2b74bc42b3005e08397236e4be0fd0

// ImGui BFFX binding
// In this binding, ImTextureID is used to store an OpenGL 'GLuint' texture
// identifier. Read the FAQ about ImTextureID in imgui.cpp.

// You can copy and use unmodified imgui_impl_* files in your project. See
// main.cpp for an example of using this. If you use this binding you'll need to
// call 4 functions: ImGui_ImplXXXX_Init(), ImGui_ImplXXXX_NewFrame(),
// ImGui::Render() and ImGui_ImplXXXX_Shutdown(). If you are new to ImGui, see
// examples/README.txt and documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

#include "brpch.h"

// BGFX/BX
#include "bgfx/bgfx.h"
#include "bgfx/embedded_shader.h"
#include "bx/allocator.h"
#include "bx/math.h"
#include "bx/timer.h"

#include "imgui_impl_bgfx.h"
#include "imgui.h"
#include "bgfx_utils.h"

#include "vs_ocornut_imgui.bin.h"
#include "fs_ocornut_imgui.bin.h"
#include "vs_imgui_image.bin.h"
#include "fs_imgui_image.bin.h"

#include "roboto_regular.ttf.h"
#include "robotomono_regular.ttf.h"
#include "icons_kenney.ttf.h"
#include "icons_font_awesome.ttf.h"

static const bgfx::EmbeddedShader kEmbeddedShaders[] =
{
    BGFX_EMBEDDED_SHADER(vs_ocornut_imgui),
    BGFX_EMBEDDED_SHADER(fs_ocornut_imgui),
    BGFX_EMBEDDED_SHADER(vs_imgui_image),
    BGFX_EMBEDDED_SHADER(fs_imgui_image),

    BGFX_EMBEDDED_SHADER_END()
};

static void* MemAlloc(size_t _size, void* _userData);
static void MemFree(void* _ptr, void* _userData);

struct Font
{
    enum Enum
    {
        Regular,
        Mono,

        Count
    };
};

class OcornutImguiContext
{
public:
    void BeginFrame(
        int32_t mx
        , int32_t my
        , uint8_t button
        , int32_t scroll
        , int width
        , int height
        , int input_char
        , bgfx::ViewId view_id
    )
    {
        view_id_ = view_id;

        ImGuiIO& io = ImGui::GetIO();
        if (input_char >= 0)
        {
            io.AddInputCharacter(input_char);
        }

        io.DisplaySize = ImVec2((float)width, (float)height);

        const int64_t now = bx::getHPCounter();
        const int64_t frameTime = now - last_;
        last_ = now;
        const double freq = double(bx::getHPFrequency());
        io.DeltaTime = float(frameTime / freq);

        io.MousePos = ImVec2((float)mx, (float)my);
        io.MouseDown[0] = 0 != (button & IMGUI_MBUT_LEFT);
        io.MouseDown[1] = 0 != (button & IMGUI_MBUT_RIGHT);
        io.MouseDown[2] = 0 != (button & IMGUI_MBUT_MIDDLE);
        io.MouseWheel = (float)(scroll - last_scroll_);
        last_scroll_ = scroll;

//#if USE_ENTRY
//        uint8_t modifiers = inputGetModifiersState();
//        io.KeyShift = 0 != (modifiers & (entry::Modifier::LeftShift | entry::Modifier::RightShift));
//        io.KeyCtrl = 0 != (modifiers & (entry::Modifier::LeftCtrl | entry::Modifier::RightCtrl));
//        io.KeyAlt = 0 != (modifiers & (entry::Modifier::LeftAlt | entry::Modifier::RightAlt));
//        for (int32_t ii = 0; ii < (int32_t)entry::Key::Count; ++ii)
//        {
//            io.KeysDown[ii] = inputGetKeyState(entry::Key::Enum(ii));
//        }
//#endif // USE_ENTRY

        ImGui::NewFrame();

        // ImGuizmo::BeginFrame();
    }

    void Create(float font_size, bx::AllocatorI* allocator)
    {
        allocator_ = allocator;

        if (allocator_ == NULL)
        {
            static bx::DefaultAllocator default_allocator;
            allocator_ = &default_allocator;
        }

        view_id_ = 255;
        last_scroll_ = 0;
        last_ = bx::getHPCounter();

        ImGui::SetAllocatorFunctions(MemAlloc, MemFree, NULL);

        imgui_ = ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();

        io.DisplaySize = ImVec2(1280.0f, 720.0f);
        io.DeltaTime = 1.0f / 60.0f;
        io.IniFilename = NULL;

        SetupStyle(true);

        bgfx::RendererType::Enum type = bgfx::getRendererType();

        program_ = bgfx::createProgram(
            bgfx::createEmbeddedShader(kEmbeddedShaders, type, "vs_ocornut_imgui"),
            bgfx::createEmbeddedShader(kEmbeddedShaders, type, "fs_ocornut_imgui"),
            true
        );

        u_imageLodEnabled = bgfx::createUniform("u_imageLodEnabled", bgfx::UniformType::Vec4);
        image_program_ = bgfx::createProgram(
            bgfx::createEmbeddedShader(kEmbeddedShaders, type, "vs_imgui_image"),
            bgfx::createEmbeddedShader(kEmbeddedShaders, type, "fs_imgui_image"),
            true
        );

        layout_
            .begin()
            .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
            .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
            .end();

        s_tex = bgfx::createUniform("s_tex", bgfx::UniformType::Sampler);

        uint8_t* data;
        int32_t width;
        int32_t height;

        {
            ImFontConfig config;
            config.FontDataOwnedByAtlas = false;
            config.MergeMode = false;

            const ImWchar* ranges = io.Fonts->GetGlyphRangesCyrillic();
            font_[Font::Regular] = io.Fonts->AddFontFromMemoryTTF((void*)s_robotoRegularTtf, sizeof(s_robotoRegularTtf), font_size, &config, ranges);
            font_[Font::Mono] = io.Fonts->AddFontFromMemoryTTF((void*)s_robotoMonoRegularTtf, sizeof(s_robotoMonoRegularTtf), font_size-3.0f, &config, ranges);

            config.MergeMode = true;
            config.DstFont = font_[Font::Regular];

            // Something about other fonts I didn't include.

            io.Fonts->GetTexDataAsRGBA32(&data, &width, &height);

            texture_ = bgfx::createTexture2D(
                (uint16_t)width,
                (uint16_t)height,
                false,
                1,
                bgfx::TextureFormat::BGRA8,
                0,
                bgfx::copy(data, width * height * 4)
            );

            // ImGui::InitDockContext();
        }
    }

    void EndFrame()
    {
        ImGui::Render();
        Render(ImGui::GetDrawData());
    }
     
    void Render(ImDrawData* draw_data)
    {
        // Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
        int fb_width = (int)(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
        int fb_height = (int)(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);
        if (fb_width <= 0 || fb_height <= 0)
            return;

        bgfx::setViewName(view_id_, "ImGui");
        bgfx::setViewMode(view_id_, bgfx::ViewMode::Sequential);

        const bgfx::Caps* caps = bgfx::getCaps();
        {
            float ortho[16];
            float x = draw_data->DisplayPos.x;
            float y = draw_data->DisplayPos.y;
            float width = draw_data->DisplaySize.x;
            float height = draw_data->DisplaySize.y;

            bx::mtxOrtho(ortho, x, x + width, y + height, y, 0.0f, 1000.0f, 0.0f, caps->homogeneousDepth);
            bgfx::setViewTransform(view_id_, NULL, ortho);
            bgfx::setViewRect(view_id_, 0, 0, uint16_t(width), uint16_t(height));
        }

        const ImVec2 clipPos = draw_data->DisplayPos;       // (0,0) unless using multi-viewports
        const ImVec2 clipScale = draw_data->FramebufferScale; // (1,1) unless using retina display which are often (2,2)

        // Render command lists
        for (int32_t ii = 0, num = draw_data->CmdListsCount; ii < num; ++ii)
        {
            bgfx::TransientVertexBuffer tvb;
            bgfx::TransientIndexBuffer tib;

            const ImDrawList* drawList = draw_data->CmdLists[ii];
            uint32_t numVertices = (uint32_t)drawList->VtxBuffer.size();
            uint32_t numIndices = (uint32_t)drawList->IdxBuffer.size();

            if (!bear::BgfxUtils::CheckAvailTransientBuffers(numVertices, layout_, numIndices))
            {
                // not enough space in transient buffer just quit drawing the rest...
                break;
            }

            bgfx::allocTransientVertexBuffer(&tvb, numVertices, layout_);
            bgfx::allocTransientIndexBuffer(&tib, numIndices, sizeof(ImDrawIdx) == 4);

            ImDrawVert* verts = (ImDrawVert*)tvb.data;
            bx::memCopy(verts, drawList->VtxBuffer.begin(), numVertices * sizeof(ImDrawVert));

            ImDrawIdx* indices = (ImDrawIdx*)tib.data;
            bx::memCopy(indices, drawList->IdxBuffer.begin(), numIndices * sizeof(ImDrawIdx));

            bgfx::Encoder* encoder = bgfx::begin();

            uint32_t offset = 0;
            for (const ImDrawCmd* cmd = drawList->CmdBuffer.begin(), *cmdEnd = drawList->CmdBuffer.end(); cmd != cmdEnd; ++cmd)
            {
                if (cmd->UserCallback)
                {
                    cmd->UserCallback(drawList, cmd);
                }
                else if (0 != cmd->ElemCount)
                {
                    uint64_t state = 0
                        | BGFX_STATE_WRITE_RGB
                        | BGFX_STATE_WRITE_A
                        | BGFX_STATE_MSAA
                        ;

                    bgfx::TextureHandle th = texture_;
                    bgfx::ProgramHandle program = program_;

                    if (NULL != cmd->TextureId)
                    {
                        union { ImTextureID ptr; struct { bgfx::TextureHandle handle; uint8_t flags; uint8_t mip; } s; } texture = { cmd->TextureId };
                        state |= 0 != (IMGUI_FLAGS_ALPHA_BLEND & texture.s.flags)
                            ? BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA)
                            : BGFX_STATE_NONE
                            ;
                        th = texture.s.handle;
                        if (0 != texture.s.mip)
                        {
                            const float lodEnabled[4] = { float(texture.s.mip), 1.0f, 0.0f, 0.0f };
                            bgfx::setUniform(u_imageLodEnabled, lodEnabled);
                            program = image_program_;
                        }
                    }
                    else
                    {
                        state |= BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);
                    }

                    // Project scissor/clipping rectangles into framebuffer space
                    ImVec4 clipRect;
                    clipRect.x = (cmd->ClipRect.x - clipPos.x) * clipScale.x;
                    clipRect.y = (cmd->ClipRect.y - clipPos.y) * clipScale.y;
                    clipRect.z = (cmd->ClipRect.z - clipPos.x) * clipScale.x;
                    clipRect.w = (cmd->ClipRect.w - clipPos.y) * clipScale.y;

                    if (clipRect.x < fb_width
                        && clipRect.y < fb_height
                        && clipRect.z >= 0.0f
                        && clipRect.w >= 0.0f)
                    {
                        const uint16_t xx = uint16_t(bx::max(clipRect.x, 0.0f));
                        const uint16_t yy = uint16_t(bx::max(clipRect.y, 0.0f));
                        encoder->setScissor(xx, yy
                            , uint16_t(bx::min(clipRect.z, 65535.0f) - xx)
                            , uint16_t(bx::min(clipRect.w, 65535.0f) - yy)
                        );

                        encoder->setState(state);
                        encoder->setTexture(0, s_tex, th);
                        encoder->setVertexBuffer(0, &tvb, 0, numVertices);
                        encoder->setIndexBuffer(&tib, offset, cmd->ElemCount);
                        encoder->submit(view_id_, program);
                    }
                }

                offset += cmd->ElemCount;
            }

            bgfx::end(encoder);
        }
    }

    void SetupStyle(bool dark)
    {
        // Doug Binks' darl color scheme
        // https://gist.github.com/dougbinks/8089b4bbaccaaf6fa204236978d165a9
        ImGuiStyle& style = ImGui::GetStyle();
        if (dark)
        {
            ImGui::StyleColorsDark(&style);
        }
        else
        {
            ImGui::StyleColorsLight(&style);
        }

        style.FrameRounding = 4.0f;
        style.WindowBorderSize = 0.0f;
    }

    bx::AllocatorI* allocator_;
    ImFont* font_[Font::Count];
    bgfx::ProgramHandle image_program_;
    ImGuiContext* imgui_;
    int64_t last_;
    int32_t last_scroll_;
    bgfx::VertexLayout layout_;
    bgfx::ProgramHandle program_;
    bgfx::TextureHandle texture_;
    bgfx::ViewId view_id_;

    bgfx::UniformHandle s_tex;
    bgfx::UniformHandle u_imageLodEnabled;
    /*
    bgfx::TextureHandle m_texture;
    ImFont* m_font[ImGui::Font::Count];
    */
};

static OcornutImguiContext context;

static void* MemAlloc(size_t size, void* user_data)
{
    BX_UNUSED(user_data);
    return BX_ALLOC(context.allocator_, size);
}

static void MemFree(void* ptr, void* user_data)
{
    BX_UNUSED(user_data);
    BX_FREE(context.allocator_, ptr);
}

void ImguiCreate(float font_size, bx::AllocatorI* allocator)
{
    context.Create(font_size, allocator);
}

void ImguiBeginFrame(int32_t mx, int32_t my, uint8_t button, int32_t scroll, uint16_t width, uint16_t height, int input_char, bgfx::ViewId view_id)
{
    context.BeginFrame(mx, my, button, scroll, width, height, input_char, view_id);
}

void ImguiEndFrame()
{
    context.EndFrame();
}
