#include "brpch.h"

#include <glm/gtc/matrix_transform.hpp>
#include <bgfx/bgfx.h>

#include "bear.h"
#include "bear/renderer/rendering_2d_system/sprite_component.h"
#include "platform/bgfx/bgfx_utils.h"

#include "basketball_components.h"
#include "offense_system.h"

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
//#include "tiny_gltf.h"

static bear::PosColorVertex cubeVertices[] =
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
	bear::World world = { "Bear Basketball" };
	bgfx::TextureHandle idle = bear::BgfxUtils::LoadTexture("assets/textures/offense_idle.ktx");

	bear::EntityHandle offensive_sprite = world.CreateEntity("Offense Sprite");
	bear::EntityHandle defensive_sprite = world.CreateEntity("Defense Sprite");

	BasketballComponent basketball_component;

	OffenseSystem attacking = { &basketball_component, offensive_sprite };

	world.AddSystem(&attacking);

	world.Run();

	return 0;
}