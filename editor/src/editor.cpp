#include "brpch.h"

#include "bear.h"
#include "bear/core/entry_point.h"

#include "ui_system.h"

namespace editor
{
	class Editor : public bear::Application
	{
	public:
		Editor() : Application("Bear Editor")
		{
			std::cout << "hello world" << std::endl;

			world_->AddSystem(new UiSystem);
		}
		
		~Editor()
		{
		}
	};
}

bear::Application* bear::CreateApplication()
{
	return new editor::Editor();
}