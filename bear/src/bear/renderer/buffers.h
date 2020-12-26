#pragma once

#include <cstdint>

#include "bear/core/core.h"

namespace bear
{
	enum class ShaderDataAttrib
	{
		Position,
		Normal,
		Tangent,
		Bitangent,
		Color0,
		Color1,
		Color2,
		Color3,
		Indices,
		Weight,
		TexCoord0,
		TexCoord1,
		TexCoord2,
		TexCoord3,
		TexCoord4,
		TexCoord5,
		TexCoord6,
		TexCoord7,
		Count
	};

	enum class ShaderDataType
	{
		kNone = 0,
		kFloat,
		kMat3,
		kMat4,
		kUint8,
		kInt,
		kBool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::kFloat: return 4;
		case ShaderDataType::kMat3: return 4 * 3 * 3;
		case ShaderDataType::kMat4: return 4 * 4 * 4;
		case ShaderDataType::kUint8: return 1;
		case ShaderDataType::kInt: return 4;
		case ShaderDataType::kBool: return 1;
		}

		//RL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	struct LayoutElement
	{
		ShaderDataAttrib Attrib;
		ShaderDataType Type;
		uint8_t Num;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;

		LayoutElement(ShaderDataAttrib attrib, uint8_t num, ShaderDataType type, bool normalized = false)
			: Attrib(attrib), Type(type), Num(num), Size(ShaderDataTypeSize(type) * num), Offset(0), Normalized(normalized) {}
	};

	class VertexLayout
	{
	public:
		VertexLayout() {}
		VertexLayout(const std::initializer_list<LayoutElement>& elements)
			: elements_(elements)
		{}

		const std::vector<LayoutElement> GetElements() const { return elements_; }
	private:
		std::vector<LayoutElement> elements_;
		uint32_t stride_ = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

		static Ref<VertexBuffer> Create(const VertexLayout& layout);
		static Ref<VertexBuffer> Create(void* data, uint32_t size, const VertexLayout& layout);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
	};
}