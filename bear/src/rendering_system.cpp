#include "rendering_system.h"

//#include <bx/math.h>
#include <iostream>

#include "components.h"

namespace bear
{
	//bgfx::ShaderHandle LoadShader(const char* filename)
	//{
	//	const char* shader_path = "???";

	//	switch (bgfx::getRendererType())
	//	{
	//	case bgfx::RendererType::Direct3D11:
	//	case bgfx::RendererType::Direct3D12: shader_path = "example_shaders/dx11/"; break;
	//	}

	//	size_t shader_len = strlen(shader_path);
	//	size_t file_len = strlen(filename);
	//	char* file_path = (char*)calloc(1, shader_len + file_len + 1);
	//	memcpy(file_path, shader_path, shader_len);
	//	memcpy(&file_path[shader_len], filename, file_len);

	//	FILE* file = fopen(file_path, "rb");
	//	fseek(file, 0, SEEK_END);
	//	long file_size = ftell(file);
	//	fseek(file, 0, SEEK_SET);

	//	const bgfx::Memory* mem = bgfx::alloc(file_size + 1);
	//	fread(mem->data, 1, file_size, file);
	//	mem->data[mem->size - 1] = '\0';
	//	fclose(file);

	//	return bgfx::createShader(mem);
	//}


	//RenderingSystem::RenderingSystem(const std::string& name)
	//	: System(name)
	//{
	//	bgfx::ShaderHandle vsh = LoadShader("vs_cubes.bin");
	//	bgfx::ShaderHandle fsh = LoadShader("fs_cubes.bin");
	//	program_ = bgfx::createProgram(vsh, fsh, true);
	//}

	//void RenderingSystem::OnUpdate(entt::registry& registry, float delta_time)
	//{
	//	const bx::Vec3 at = { 0.0f, 0.0f, 0.0f };
	//	const bx::Vec3 eye = { 0.0f, 0.0f, -5.0f };
	//	float view[16];
	//	bx::mtxLookAt(view, eye, at);
	//	float proj[16];
	//	bx::mtxProj(proj, 45.0f, float(1280) / float(720), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
	//	bgfx::setViewTransform(0, view, proj);

	//	auto registry_view = registry.view<MeshFilterComponent, TransformComponent>();
	//	for (auto entity : registry_view)
	//	{
	//		auto [mesh_filter, transform] = registry_view.get<MeshFilterComponent, TransformComponent>(entity);
	//		//std::cout << "Test" << std::endl;
	//		bgfx::setTransform(transform);
	//		bgfx::setVertexBuffer(0, mesh_filter.Vbh);
	//		bgfx::setIndexBuffer(mesh_filter.Ibh);

	//		bgfx::submit(0, program_);
	//	}
	//	
	//	bgfx::frame();
	//	counter_++;
	//}

}