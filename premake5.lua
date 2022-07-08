-- Project
workspace "Project"
	architecture "x64"
	startproject "Project"

	configurations
	{
		"Debug",
		"Release"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to Core engine
IncludeDir = {}
IncludeDir["GLFW"] = "vendor/GLFW/include"
IncludeDir["Glad"] = "vendor/Glad/include"
IncludeDir["ImGui"] = "vendor/imgui"
IncludeDir["glm"] = "vendor/glm"
IncludeDir["json"] = "vendor/json"
IncludeDir["stb_image"] = "vendor/stb_image"

group "Dependencies"
	include "core/vendor/GLFW"
	include "core/vendor/Glad"
	include "core/vendor/imgui"
group ""

include "Core"
include "Project"

