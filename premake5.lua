workspace "Game_Engine"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Game_Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "Game_Engine/vendor/Glad/include"
IncludeDir["ImGui"] = "Game_Engine/vendor/imgui"
IncludeDir["glm"] = "Game_Engine/vendor/glm"
IncludeDir["stb_image"] = "Game_Engine/vendor/stb_image"

include "Game_Engine/vendor/GLFW"
include "Game_Engine/vendor/Glad"
include "Game_Engine/vendor/imgui"

project "Game_Engine"
	location "Game_Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gepch.h"
	pchsource "Game_Engine/src/gepch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links { 
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"PLATFORM_WINDOWS",
			"BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "DIST"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Game_Engine/vendor/spdlog/include",
		"Game_Engine/src",
		"Game_Engine/vendor",
		"%{IncludeDir.glm}"
	}

	links {
		"Game_Engine",
		"ImGui"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		optimize "on"

	filter "configurations:Dist"
		defines "DIST"
		optimize "on"
