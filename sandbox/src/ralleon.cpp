#include "brpch.h"

#include <glm/gtc/matrix_transform.hpp>
#include <bgfx/bgfx.h>

#include <bx/math.h>

#include "bear.h"
#include "bear/core/entry_point.h"
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
		world_->AddSystem(new PlayerControllerSystem);
		world_->AddSystem(new CameraFollowSystem);

		bear::EntityHandle mesh_entity = world_->CreateEntity("Mesh");
		{
			//bear::Mesh::Create("assets/gltf/bunny.bin");
			mesh_entity.AddComponent<bear::MeshTestComponent>(bear::Mesh::Create("assets/gltf/sphere.bin"));
			bear::TransformComponent tc;
			tc.SetPosition({ 0.0f, 1.0f, 0.0f });
			mesh_entity.AddComponent<bear::TransformComponent>(tc);
		}

		auto target_indicator = world_->CreateEntity("Target Indicator");
		{
			bear::TransformComponent tc;
			tc.SetPosition({ 999, 999, 999 });
			target_indicator.AddComponent<bear::TransformComponent>(tc);
			target_indicator.AddComponent<TargetIndicatorComponent>();
			target_indicator.AddComponent<bear::MeshFilterComponent>(bear::Shapes::kDiamond);
		}

		/*bear::EntityHandle image = world_->CreateEntity("Image");
		{
			bear::RectTransformComponent rtc;
			rtc.SetPosition({ 0.0f, -240.0f, -1.0f });
			rtc.SetHeight(240.0f);
			rtc.SetWidth(1280.0f);
			image.AddComponent<bear::RectTransformComponent>(rtc);

			image.AddComponent<bear::ImageComponent>(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		}*/

		bear::EntityHandle castbar = world_->CreateEntity("Option 1");
		{
			bear::RectTransformComponent rtc;
			rtc.SetPosition({ 0.0f, -240.0f, -10.0f });
			rtc.SetHeight(36.0f);
			rtc.SetWidth(240.0f);
			castbar.AddComponent<bear::RectTransformComponent>(rtc);

			castbar.AddComponent<bear::ImageComponent>(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
			CastbarComponent c;
			c.Duration = std::chrono::seconds(10);
			c.Reverse = true;
			c.StartTime = std::chrono::high_resolution_clock::now();
			castbar.AddComponent<CastbarComponent>(c);
		}

		bear::EntityHandle camera = world_->CreateEntity("Main Camera");
		{
			bear::TransformComponent tc;
			camera.AddComponent<bear::TransformComponent>(tc);

			camera.AddComponent<bear::PerspectiveCameraComponent>(45.0f, 0.1f, 100.0f);
		}

		{
			bear::EntityHandle terrain = world_->CreateEntity("Terrain");

			bear::TransformComponent tc;
			tc.SetPosition({ 0.0f, -0.5f, 0.0f });
			tc.SetScale({ 20.0f, 0.5f, 20.0f });
			terrain.AddComponent<bear::TransformComponent>(tc);

			terrain.AddComponent<bear::MeshFilterComponent>(bear::Shapes::kCube);
			terrain.AddComponent<bear::MaterialComponent>(glm::vec4{ 0.5f, 0.6f, 0.2f, 1.0f });
			terrain.AddComponent<bear::RigidBodyConstructorComponent>(rp3d::BodyType::STATIC);
			terrain.AddComponent<bear::BoxColliderConstructorComponent>(glm::vec3(20.0f, 0.5f, 20.0f));
		}

		{
			bear::EntityHandle player = world_->CreateEntity("Player");

			bear::TransformComponent tc;
			tc.SetPosition({ 0.0f, 1.5f, 0.0f });
			tc.SetScale({ 0.4f, 1.0f, 0.4f });
			player.AddComponent<bear::TransformComponent>(tc);

			player.AddComponent<bear::MeshFilterComponent>(bear::Shapes::kDiamond);
			player.AddComponent<bear::MaterialComponent>(glm::vec4{ 0.1f, 1.0f, 0.3f, 1.0f });
			player.AddComponent<CameraFollowComponent>(camera, glm::vec3(0.0f, 2.0f, 10.0f));
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

		std::ifstream t("terrain.json");
		std::stringstream buffer;
		buffer << t.rdbuf();

		world_->PopulateFromJson(buffer.str());
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