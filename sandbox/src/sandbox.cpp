#include "brpch.h"

#include <glm/gtc/matrix_transform.hpp>
#include <bgfx/bgfx.h>

#include "bear.h"
#include "bear/renderer/rendering_system/rendering_components.h"
#include "platform/bgfx/bgfx_utils.h"

#include "camera_follow_system.h"
#include "player_controller_system.h"
#include "targetting_system.h"
#include "ability_system/ability_system.h"

using namespace ralleon;

int main(void)
{
	bear::World world = { "Bear Sandbox" };
	AbilityCatalog::Init();
	world.AddSystem(new PlayerControllerSystem);
	world.AddSystem(new CameraFollowSystem);

	bear::EntityHandle camera = world.CreateEntity("Main Camera");
	{
		const glm::vec3 at = { 0.0f, 0.0f, 0.0f };
		const glm::vec3 eye = { 0.0f, 0.0f, -10.0f };
		glm::mat4 view = glm::lookAt(eye, at, { 0.0f, 1.0f, 0.0f });
		camera.AddComponent<bear::TransformComponent>(view);

		glm::mat4 proj = glm::perspective(glm::radians(45.0f), float(1280) / float(720), 0.1f, 100.0f);
		camera.AddComponent<bear::PerspectiveCameraComponent>(proj);
	}

	{
		bear::EntityHandle player = world.CreateEntity("Player");

		glm::mat4 mat = glm::mat4(1.0f);
		mat = glm::translate(mat, { 0.0f, 0.5f, 0.0f });
		mat = glm::scale(mat, { 0.4f, 1.0f, 0.4f });
		player.AddComponent<bear::TransformComponent>(mat);
		player.AddComponent<bear::MeshFilterComponent>(bear::Shapes::kDiamond);
		player.AddComponent<CameraFollowComponent>(camera);
		player.AddComponent<PlayerControllerComponent>(12.0f, 90.0f);
		player.AddComponent<CharacterComponent>();
		player.AddComponent<AbilityCasterComponent>();

		world.AddSystem(new TargettingSystem(player));
		world.AddSystem(new AbilityCastingSystem(player));
	}

	{
		bear::EntityHandle npc = world.CreateEntity("Enemy");
		glm::mat4 mat = glm::mat4(1.0f);
		mat = glm::translate(mat, { 0.0f, 0.25f, -10.0f });
		mat = glm::scale(mat, { 0.5f, 0.5, 0.5f });
		npc.AddComponent<bear::TransformComponent>(mat);
		npc.AddComponent<bear::MeshFilterComponent>(bear::Shapes::kCube);
		npc.AddComponent<CharacterComponent>();
		npc.AddComponent<AbilityCasterComponent>();
	}

	{
		bear::EntityHandle tree = world.CreateEntity("Tree");

		glm::mat4 mat = glm::mat4(1.0f);
		mat = glm::translate(mat, { 5.0f, 2.0f, -5.0f });
		mat = glm::scale(mat, { 1.0f, 4.0f, 1.0f });
		tree.AddComponent<bear::TransformComponent>(mat);
		tree.AddComponent<bear::MeshFilterComponent>(bear::Shapes::kCube);
	}

	{
		bear::EntityHandle tree = world.CreateEntity("Tree");

		glm::mat4 mat = glm::mat4(1.0f);
		mat = glm::translate(mat, { -5.0f, 2.0f, -10.0f });
		mat = glm::scale(mat, { 1.0f, 4.0f, 1.0f });
		tree.AddComponent<bear::TransformComponent>(mat);
		tree.AddComponent<bear::MeshFilterComponent>(bear::Shapes::kCube);
	}

	world.Run();

	return 0;
}