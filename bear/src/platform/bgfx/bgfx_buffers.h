#pragma once

#include "bear/renderer/buffers.h"

#include <bgfx/bgfx.h>

namespace bear
{
	class BGFXVertexBuffer : public VertexBuffer
	{
	public:
		BGFXVertexBuffer(const bear::VertexLayout& layout);
		BGFXVertexBuffer(const bgfx::VertexLayout& layout);
		BGFXVertexBuffer(void* data, uint32_t size, const bear::VertexLayout& layout);
		BGFXVertexBuffer(void* data, uint32_t size, const bgfx::VertexLayout& layout);
		virtual ~BGFXVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetData(const void* data, uint32_t size) override;
	private:
		bgfx::VertexLayout CreateLayout(const VertexLayout& layout);

		bgfx::DynamicVertexBufferHandle handle_;
		void* data_ = nullptr;
		uint32_t size_ = 0;

		//VertexLayout layout_;
		bgfx::VertexLayout layout_;
	};

	class BGFXIndexBuffer : public IndexBuffer
	{
	public:
		BGFXIndexBuffer(const void* indices, uint32_t count);
		virtual ~BGFXIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		bgfx::IndexBufferHandle handle_;
		const void* indices = nullptr;
		uint32_t size_ = 0;
	};
}