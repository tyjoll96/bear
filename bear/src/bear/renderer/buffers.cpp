#include "brpch.h"
#include "buffers.h"

#include "platform/bgfx/bgfx_buffers.h"

namespace bear
{
	Ref<VertexBuffer> VertexBuffer::Create(const VertexLayout& layout)
	{
		return CreateRef<BGFXVertexBuffer>(layout);
	}

	Ref<VertexBuffer> VertexBuffer::Create(void* data, uint32_t size, const VertexLayout& layout)
	{
		return CreateRef<BGFXVertexBuffer>(data, size, layout);
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		return Ref<IndexBuffer>();
	}
}