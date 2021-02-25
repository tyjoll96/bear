#include "brpch.h"
#include "bgfx_utils.h"

#include <bimg/bimg.h>
#include <bx/bx.h>
#include <bx/file.h>
#include <bx/readerwriter.h>

#include "bounds.h"

#include <tinystl/string.h>

namespace bgfx
{
	int32_t read(bx::ReaderI* _reader, bgfx::VertexLayout& _layout, bx::Error* _err = NULL);
}

namespace bear
{
	namespace BgfxUtils
	{
		BGFXMesh LoadMesh(const char* file_path)
		{
			BGFXMesh mesh;

			constexpr uint32_t kChunkVertexBuffer			= BX_MAKEFOURCC('V', 'B', ' ', 0x1);
			constexpr uint32_t kChunkVertexBufferCompressed = BX_MAKEFOURCC('V', 'B', 'C', 0x0);
			constexpr uint32_t kChunkIndexBuffer			= BX_MAKEFOURCC('I', 'B', ' ', 0x0);
			constexpr uint32_t kChunkIndexBufferCompressed	= BX_MAKEFOURCC('I', 'B', 'C', 0x1);
			constexpr uint32_t kChunkPrimitive				= BX_MAKEFOURCC('P', 'R', 'I', 0x0);

			bx::DefaultAllocator da;
			bx::FileReader fr;

			if (bx::open(&fr, file_path))
			{
				uint32_t chunk;
				bx::Error err;
				while (4 == bx::read(&fr, chunk, &err)
					&& err.isOk())
				{
					std::cout << "current chunk " << chunk << std::endl;
					switch (chunk)
					{
					case kChunkVertexBuffer:
					{
						std::cout << "Test vb" << std::endl;
						Sphere sphere;
						Aabb aabb;
						Obb obb;
						bx::read(&fr, sphere);
						bx::read(&fr, aabb);
						bx::read(&fr, obb);

						bgfx::VertexLayout vl;
						bgfx::read(&fr, vl);
						uint16_t stride = vl.getStride();

						uint16_t num_vertices;
						bx::read(&fr, num_vertices);
						std::cout << "Number of vertices: " << num_vertices << std::endl;
						const bgfx::Memory* mem = bgfx::alloc(num_vertices * stride);
						bx::read(&fr, mem->data, mem->size);

						/*if (_ramcopy)
						{
							group.m_vertices = (uint8_t*)BX_ALLOC(allocator, group.m_numVertices * stride);
							bx::memCopy(group.m_vertices, mem->data, mem->size);
						}*/

						// bgfx::DynamicVertexBufferHandle vbh = bgfx::createDynamicVertexBuffer(mem, vl);
						BGFXVertexBuffer vb(mem->data, mem->size, vl);
						mesh.SetVb(CreateRef<BGFXVertexBuffer>(vb));
					}
					break;
					case kChunkVertexBufferCompressed:
					{
						std::cout << "Test vbc" << std::endl;
					}
					break;
					case kChunkIndexBuffer:
					{
						std::cout << "Test ib" << std::endl;
						uint32_t num_indices;
						bx::read(&fr, num_indices);
						const bgfx::Memory* mem = bgfx::alloc(num_indices * 2);
						bx::read(&fr, mem->data, mem->size);
						/*if (_ramcopy)
						{
							group.m_indices = (uint16_t*)BX_ALLOC(allocator, group.m_numIndices * 2);
							bx::memCopy(group.m_indices, mem->data, mem->size);
						}*/

						BGFXIndexBuffer ib(mem->data, mem->size);
						mesh.SetIb(CreateRef<BGFXIndexBuffer>(ib));
					}
					break;
					case kChunkIndexBufferCompressed:
					{
						std::cout << "Test ibc" << std::endl;
					}
					break;
					case kChunkPrimitive:
					{
						/*uint16_t len;
						read(_reader, len);

						stl::string material;
						material.resize(len);
						read(_reader, const_cast<char*>(material.c_str()), len);

						uint16_t num;
						read(_reader, num);

						for (uint32_t ii = 0; ii < num; ++ii)
						{
							read(_reader, len);

							stl::string name;
							name.resize(len);
							read(_reader, const_cast<char*>(name.c_str()), len);

							Primitive prim;
							read(_reader, prim.m_startIndex);
							read(_reader, prim.m_numIndices);
							read(_reader, prim.m_startVertex);
							read(_reader, prim.m_numVertices);
							read(_reader, prim.m_sphere);
							read(_reader, prim.m_aabb);
							read(_reader, prim.m_obb);

							group.m_prims.push_back(prim);
						}

						m_groups.push_back(group);
						group.reset();*/
						return mesh;
						std::cout << "Test" << std::endl;
					}
					break;
					default:
						//bx::skip(&fr, 0);
						//DBG("%08x at %d", chunk, );
						break;
					}
				}
			}
			return mesh;
		}

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

				bx::close(&fr);
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
				bx::close(&fr);
			}
			else
			{
				std::cout << "Failed to open file" << std::endl;
			}

			return handle;
		}
	}
}