#include "brpch.h"

#include "bear.h"
#include "bear/core/entry_point.h"

namespace editor
{
	class Editor : public bear::Application
	{
	public:
		Editor()
			: Application("Bear Editor")
		{
			std::cout << "hello world" << std::endl;
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