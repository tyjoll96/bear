#pragma once

#include <bgfx/bgfx.h>

namespace bear
{
	namespace BgfxUtils
	{
		bgfx::ShaderHandle LoadShader(const char* file_path);
		bgfx::TextureHandle LoadTexture(const char* file_path);
	};
}