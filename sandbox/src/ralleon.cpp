#include "brpch.h"

#include <glm/gtc/matrix_transform.hpp>
#include <bgfx/bgfx.h>

#include "bear.h"
#include "bear/core/entry_point.h"
#include "bear/physics/physics_system.h"
#include "bear/physics/physics_components.h"
#include "bear/renderer/rendering_system/rendering_components.h"
#include "bear/renderer/rendering_2d_system/sprite_component.h"
#include "platform/bgfx/bgfx_utils.h"

#include "camera_follow_system.h"
#include "player_controller_system.h"
#include "targetting_system.h"
#include "ability_system/ability_system.h"

namespace ralleon
{
class Ralleon : public bear::Application
{
public:
	Ralleon()
		: Application("Ralleon")
	{
		AbilityCatalog::Init();
		world_->AddSystem(new bear::PhysicsSystem());
		world_->AddSystem(new PlayerControllerSystem);
		world_->AddSystem(new CameraFollowSystem);

		bear::EntityHandle camera = world_->CreateEntity("Main Camera");
		{
			const glm::vec3 at = { 0.0f, 0.0f, 0.0f };
			const glm::vec3 eye = { 0.0f, 0.0f, -10.0f };
			glm::mat4 view = glm::lookAt(eye, at, { 0.0f, 1.0f, 0.0f });
			camera.AddComponent<bear::TransformComponent>(view);

			glm::mat4 proj = glm::perspective(glm::radians(45.0f), float(1280) / float(720), 0.1f, 100.0f);
			camera.AddComponent<bear::PerspectiveCameraComponent>(proj);
		}

		{
			bear::EntityHandle terrain = world_->CreateEntity("Terrain");

			bear::TransformComponent tc;
			tc.SetPosition({ 0.0f, -0.5f, 0.0f });
			tc.SetScale({ 10.0f, 0.5f, 10.0f });
			terrain.AddComponent<bear::TransformComponent>(tc);
			terrain.AddComponent<bear::MeshFilterComponent>(bear::Shapes::kCube);
			terrain.AddComponent<bear::MaterialComponent>(glm::vec4{ 0.5f, 0.6f, 0.2f, 1.0f });
			terrain.AddComponent<bear::RigidBodyConstructorComponent>(rp3d::BodyType::STATIC);
			terrain.AddComponent<bear::BoxColliderConstructorComponent>(glm::vec3(10.0f, 0.5f, 10.0f));
		}

		{
			bear::EntityHandle player = world_->CreateEntity("Player");

			bear::TransformComponent tc;
			tc.SetPosition({ 0.0f, 1.5f, 0.0f });
			tc.SetScale({ 0.4f, 1.0f, 0.4f });
			player.AddComponent<bear::TransformComponent>(tc);
			player.AddComponent<bear::MeshFilterComponent>(bear::Shapes::kDiamond);
			player.AddComponent<bear::MaterialComponent>(glm::vec4{ 0.1f, 1.0f, 0.3f, 1.0f });
			player.AddComponent<CameraFollowComponent>(camera);
			player.AddComponent<PlayerControllerComponent>(12.0f, 90.0f);
			player.AddComponent<CharacterComponent>();
			player.AddComponent<AbilityCasterComponent>();
			player.AddComponent<bear::RigidBodyConstructorComponent>(rp3d::BodyType::DYNAMIC);
			player.AddComponent<bear::BoxColliderConstructorComponent>(glm::vec3(1.0f));

			world_->AddSystem(new TargettingSystem(player));
			world_->AddSystem(new AbilityCastingSystem(player));
		}

		{
			bear::EntityHandle npc = world_->CreateEntity("Enemy");

			bear::TransformComponent tc;
			tc.SetPosition({ 0.0f, 1.0f, -8.0f });
			tc.SetScale(glm::vec3(0.5f));

			npc.AddComponent<bear::TransformComponent>(tc);
			npc.AddComponent<bear::MeshFilterComponent>(bear::Shapes::kCube);
			npc.AddComponent<bear::MaterialComponent>(glm::vec4{ 1.0f, 0.2f, 0.2f, 1.0f });
			npc.AddComponent<CharacterComponent>();
			npc.AddComponent<AbilityCasterComponent>();
			npc.AddComponent<bear::RigidBodyConstructorComponent>(rp3d::BodyType::DYNAMIC);
			npc.AddComponent<bear::BoxColliderConstructorComponent>(glm::vec3(0.5f));
		}

		{
			bear::EntityHandle tree = world_->CreateEntity("Tree");

			glm::mat4 mat = glm::mat4(1.0f);
			mat = glm::translate(mat, { 5.0f, 2.0f, -5.0f });
			mat = glm::scale(mat, { 1.0f, 4.0f, 1.0f });
			tree.AddComponent<bear::TransformComponent>(mat);
			tree.AddComponent<bear::MeshFilterComponent>(bear::Shapes::kCube);
		}

		{
			bear::EntityHandle tree = world_->CreateEntity("Tree");

			glm::mat4 mat = glm::mat4(1.0f);
			mat = glm::translate(mat, { -5.0f, 2.0f, -10.0f });
			mat = glm::scale(mat, { 1.0f, 4.0f, 1.0f });
			tree.AddComponent<bear::TransformComponent>(mat);
			tree.AddComponent<bear::MeshFilterComponent>(bear::Shapes::kCube);
		}
	}

	~Ralleon()
	{
	}
};
}

bear::Application* bear::CreateApplication()
{
	return new ralleon::Ralleon();
}