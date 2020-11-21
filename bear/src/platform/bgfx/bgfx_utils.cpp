#include "brpch.h"
#include "bgfx_utils.h"

#include <bimg/bimg.h>
#include <bx/bx.h>
#include <bx/file.h>

namespace bear
{
	namespace BgfxUtils
	{
		bgfx::ShaderHandle LoadShader(const char* file_path)
		{
			bgfx::ShaderHandle handle = BGFX_INVALID_HANDLE;

			void* data;
			uint32_t size;
			bx::DefaultAllocator da;
			bx::FileReader fr;
			if (bx::open(&fr, file_path))
			{
				size = (uint32_t)bx::getSize(&fr);
				const bgfx::Memory* mem = bgfx::alloc(size + 1);
				bx::read(&fr, mem->data, size);
				bx::close(&fr);
				mem->data[mem->size - 1] = '\0';

				handle = bgfx::createShader(mem);
			}
			else
			{
				std::cout << "Failed to open file" << std::endl;
			}

			return handle;
		}

		bgfx::TextureHandle LoadTexture(const char* file_path)
		{
			bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;

			void* data;
			uint32_t size;
			bx::DefaultAllocator da;
			bx::FileReader fr;
			if (bx::open(&fr, file_path))
			{
				size = (uint32_t)bx::getSize(&fr);
				data = bx::alloc(&da, size);
				bx::read(&fr, data, size);
				bx::close(&fr);

				bimg::ImageContainer* ktx_container = bimg::imageParseKtx(&da, data, size, nullptr);

				const bgfx::Memory* mem = bgfx::makeRef(
					ktx_container->m_data,
					ktx_container->m_size,
					0,
					ktx_container
				);

				handle = bgfx::createTexture2D(
					uint16_t(ktx_container->m_width)
					, uint16_t(ktx_container->m_height)
					, 1 < ktx_container->m_numMips
					, ktx_container->m_numLayers
					, bgfx::TextureFormat::Enum(ktx_container->m_format)
					, 0
					, mem
				);

				bx::free(&da, data, 0);
			}
			else
			{
				std::cout << "Failed to open file" << std::endl;
			}

			return handle;
		}
	}
}