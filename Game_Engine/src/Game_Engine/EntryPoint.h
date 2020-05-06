#pragma once

#ifdef PLATFORM_WINDOWS

extern GameEngine::Application* GameEngine::CreateApplication();

int main(int argc, char** argv) {
	GameEngine::Log::Init();
	GE_CORE_WARN("Initialize Log");

	auto app = GameEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif