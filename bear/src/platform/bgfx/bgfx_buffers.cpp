#include "brpch.h"
#include "bgfx_buffers.h"

namespace bear
{
	static bgfx::Attrib::Enum ShaderDataAttribToBgfx(ShaderDataAttrib attrib)
	{
		switch (attrib)
		{
		case ShaderDataAttrib::Position: return bgfx::Attrib::Position;
		case ShaderDataAttrib::Normal: return bgfx::Attrib::Normal;
		case ShaderDataAttrib::Tangent: return bgfx::Attrib::Tangent;
		case ShaderDataAttrib::Bitangent: return bgfx::Attrib::Bitangent;
		case ShaderDataAttrib::Color0: return bgfx::Attrib::Color0;
		case ShaderDataAttrib::Color1: return bgfx::Attrib::Color1;
		case ShaderDataAttrib::Color2: return bgfx::Attrib::Color2;
		case ShaderDataAttrib::Color3: return bgfx::Attrib::Color3;
		case ShaderDataAttrib::Indices: return bgfx::Attrib::Indices;
		case ShaderDataAttrib::Weight: return bgfx::Attrib::Weight;
		case ShaderDataAttrib::TexCoord0: return bgfx::Attrib::TexCoord0;
		case ShaderDataAttrib::TexCoord1: return bgfx::Attrib::TexCoord1;
		case ShaderDataAttrib::TexCoord2: return bgfx::Attrib::TexCoord2;
		case ShaderDataAttrib::TexCoord3: return bgfx::Attrib::TexCoord3;
		case ShaderDataAttrib::TexCoord4: return bgfx::Attrib::TexCoord4;
		case ShaderDataAttrib::TexCoord5: return bgfx::Attrib::TexCoord5;
		case ShaderDataAttrib::TexCoord6: return bgfx::Attrib::TexCoord6;
		case ShaderDataAttrib::TexCoord7: return bgfx::Attrib::TexCoord7;
		case ShaderDataAttrib::Count: return bgfx::Attrib::Count;
		}

		//RL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return bgfx::Attrib::Count;
	}

	static bgfx::AttribType::Enum ShaderDataTypeToBgfx(ShaderDataType attrib)
	{
		switch (attrib)
		{
		case ShaderDataType::kFloat: return bgfx::AttribType::Float;
		case ShaderDataType::kUint8: return bgfx::AttribType::Uint8;
		case ShaderDataType::kInt: return bgfx::AttribType::Int16;
		}

		//RL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return bgfx::AttribType::Uint8;
	}

	BGFXVertexBuffer::BGFXVertexBuffer(const VertexLayout& layout)
	{
		layout_ = CreateLayout(layout);
		handle_ = bgfx::createDynamicVertexBuffer(nullptr, layout_);
	}

	BGFXVertexBuffer::BGFXVertexBuffer(void* data, uint32_t size, const VertexLayout& layout)
		: data_(data), size_(size)
	{
		layout_ = CreateLayout(layout);
		handle_ = bgfx::createDynamicVertexBuffer(bgfx::makeRef(data, size), layout_);
	}

	BGFXVertexBuffer::~BGFXVertexBuffer()
	{
	}

	void BGFXVertexBuffer::Bind() const
	{
		bgfx::setVertexBuffer(0, handle_);
	}

	void BGFXVertexBuffer::Unbind() const
	{
		bgfx::setVertexBuffer(0, nullptr);
	}

	void BGFXVertexBuffer::SetData(const void* data, uint32_t size)
	{
	}

	bgfx::VertexLayout BGFXVertexBuffer::CreateLayout(const VertexLayout& layout)
	{
		bgfx::VertexLayout bgfx_layout;

		bgfx_layout.begin();

		for (auto element : layout.GetElements())
		{
			bgfx_layout.add(
				ShaderDataAttribToBgfx(element.Attrib),
				element.Num,
				ShaderDataTypeToBgfx(element.Type),
				element.Normalized);
		}

		bgfx_layout.end();

		return bgfx_layout;
	}
}