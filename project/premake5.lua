project "Project"
	kind "ConsoleApp"
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
	}

	includedirs
	{
		"include",
		"../core/include",
		"../core/vendor",
		"../core/%{IncludeDir.glm}",
		"../core/%{IncludeDir.Glad}",
		"../core/%{IncludeDir.ImGui}",
	}

	links
	{
		"Core"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"CORE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CORE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CORE_RELEASE"
		runtime "Release"
        optimize "on"
