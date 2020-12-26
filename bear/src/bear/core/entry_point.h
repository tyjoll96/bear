#pragma once

extern bear::Application* bear::CreateApplication();

int main(int argc, char** argv)
{
	auto app = bear::CreateApplication();

	app->Run();

	delete app;
}