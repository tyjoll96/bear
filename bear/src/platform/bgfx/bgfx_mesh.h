#pragma once

#include "bear/renderer/mesh.h"

#include <bgfx/bgfx.h>

#include "bgfx_buffers.h"

namespace bear
{
	class BGFXMesh : public Mesh
	{
	public:
		BGFXMesh();
		//BGFXMesh(const char* file_path);
		BGFXMesh(BGFXVertexBuffer* vb, BGFXIndexBuffer* ib);
		virtual ~BGFXMesh();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void SetVb(Ref<BGFXVertexBuffer> vb) { vb_ = vb; }
		void SetIb(Ref<BGFXIndexBuffer> ib) { ib_ = ib; }
	private:
		Ref<BGFXVertexBuffer> vb_ = nullptr;
		Ref<BGFXIndexBuffer> ib_ = nullptr;
	};
}