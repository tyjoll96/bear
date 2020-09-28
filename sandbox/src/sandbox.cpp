#include <iostream>
#include <cstdio>

//#include <bx/math.h>
//#include <bgfx/bgfx.h>
//#include <bgfx/platform.h>

#include "bear.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
//#include "tiny_gltf.h"

static std::vector<bear::PosColorVertex> cubeVertices =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t cubeTriList[] =
{
	0, 1, 2,
	1, 3, 2,
	4, 6, 5,
	5, 6, 7,
	0, 2, 4,
	4, 2, 6,
	1, 5, 3,
	5, 7, 3,
	0, 4, 1,
	4, 5, 1,
	2, 3, 6,
	6, 3, 7,
};

int main(void)
{
	/*tinygltf::Model model;
	tinygltf::TinyGLTF loader;
	std::string err;
	std::string warn;

	bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, "assets/gltf/arrow.glb");*/

	/*if (!warn.empty()) {
		printf("Warn: %s\n", warn.c_str());
	}

	if (!err.empty()) {
		printf("Err: %s\n", err.c_str());
	}

	if (!ret) {
		printf("Failed to parse glTF\n");
		return -1;
	}*/

	bear::World world = { "Bear Sandbox" };

	bear::EntityHandle handle = world.CreateEntity("Test");
	//bgfx::VertexLayout layout;
	//layout.begin()
	//	.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
	//	.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
	//	// .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
	//	.end();

	//std::vector<unsigned char> vertex_buffer;

	//for (size_t i = 0; i < model.accessors[0].count; i++)
	//{
	//	uint32_t vertex_offset = i * layout.getStride();
	//	uint32_t buffer_offset = i * 12; // replace hard coded size

	//	vertex_buffer.insert(
	//		vertex_buffer.begin() + vertex_offset + layout.getOffset(bgfx::Attrib::Position),
	//		model.buffers[0].data.begin() + model.bufferViews[0].byteOffset + buffer_offset,
	//		model.buffers[0].data.begin() + model.bufferViews[0].byteOffset + buffer_offset + 12
	//	);

	//	vertex_buffer.insert(
	//		vertex_buffer.begin() + vertex_offset + layout.getOffset(bgfx::Attrib::Normal),
	//		model.buffers[0].data.begin() + model.bufferViews[1].byteOffset + buffer_offset,
	//		model.buffers[0].data.begin() + model.bufferViews[1].byteOffset + buffer_offset + 12
	//	);
	//}

	/*std::cout << vertex_buffer.size();

	handle.AddComponent<bear::MeshFilterComponent>(&vertex_buffer[0], vertex_buffer.size() * 3 * 4, layout, &model.buffers[0].data[model.bufferViews[3].byteOffset], model.bufferViews[3].byteLength);

	float mtx[16];
	bx::mtxIdentity(mtx);
	bx::mtxRotateXY(mtx, 0.785398f, 0.785398f);
	handle.AddComponent<bear::TransformComponent>(mtx);*/

	world.Run();

	return 0;
}