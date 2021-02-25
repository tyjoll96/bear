#include "brpch.h"
#include "mesh.h"

#include "platform/bgfx/bgfx_utils.h"

namespace bear
{
    Ref<Mesh> Mesh::Create(const char* file_path)
    {
        return CreateRef<BGFXMesh>(BgfxUtils::LoadMesh(file_path));
        //return CreateRef<BGFXMesh>(file_path);
    }
}