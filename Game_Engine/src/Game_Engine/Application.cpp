#include "gepch.h"
#include "Application.h"

#include "Game_Engine/Events/ApplicationEvent.h"
#include "Game_Engine/Log.h"

namespace GameEngine {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::Run() {
		WindowResizeEvent e(1200, 720);
		GE_TRACE(e.ToString());

		while(true);
	}

}