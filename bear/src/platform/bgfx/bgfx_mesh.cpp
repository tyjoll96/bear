#include "brpch.h"
#include "bgfx_mesh.h"

namespace bear
{
	/*BGFXMesh::BGFXMesh(const char* file_path)
	{

	}*/

	BGFXMesh::BGFXMesh()
	{
	}

	BGFXMesh::BGFXMesh(BGFXVertexBuffer* vb, BGFXIndexBuffer* ib)
		: vb_(vb), ib_(ib)
	{}

	BGFXMesh::~BGFXMesh()
	{
	}

	void BGFXMesh::Bind() const
	{
		vb_->Bind();
		ib_->Bind();
	}

	void BGFXMesh::Unbind() const
	{
	}
}