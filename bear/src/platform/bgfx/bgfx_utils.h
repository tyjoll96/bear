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

		inline bool CheckAvailTransientBuffers(uint32_t num_vertices, const bgfx::VertexLayout& layout, uint32_t num_indices)
		{
			return num_vertices == bgfx::getAvailTransientVertexBuffer(num_vertices, layout)
				&& (0 == num_indices || num_indices == bgfx::getAvailTransientIndexBuffer(num_indices))
				;
		}
	};
}