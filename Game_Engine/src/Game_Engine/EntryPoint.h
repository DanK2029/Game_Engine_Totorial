#pragma once

#ifdef PLATFORM_WINDOWS

extern GameEngine::Application* GameEngine::CreateApplication();

int main(int argc, char** argv) {
	GameEngine::Log::Init();
	GE_CORE_WARN("Initialize Log");
	int a = 5;
	GE_INFO("Hello var={0}", a);

	auto app = GameEngine::CreateApplication();
	app->Run();
	delete app;
}

#endif