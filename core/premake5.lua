project "Core"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/**.h",
		"include/**.hpp",
		"include/**.cpp",
		"src/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CORE_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "CORE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CORE_RELEASE"
		runtime "Release"