#pragma once

#include <bgfx/bgfx.h>
#include <bimg/bimg.h>

#include "bgfx_mesh.h"

#include <tinystl/allocator.h>
#include <tinystl/vector.h>
namespace stl = tinystl;
#include "bounds.h"

namespace bear
{
	namespace BgfxUtils
	{
		BGFXMesh LoadMesh(const char* file_path);
		bgfx::ShaderHandle LoadShader(const char* file_path);
		bgfx::TextureHandle LoadTexture(const char* file_path);
	};
}