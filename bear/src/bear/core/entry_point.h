#pragma once

extern bear::Application* bear::CreateApplication();

int main(int argc, char** argv)
{
	bear::Log::Init();

	auto app = bear::CreateApplication();

	app->Run();

	delete app;
}