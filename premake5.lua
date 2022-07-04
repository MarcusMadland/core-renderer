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
IncludeDir["TinyGLTF"] = "vendor/tinygltf"

group "Dependencies"
	include "core/vendor/GLFW"
	include "core/vendor/Glad"
	include "core/vendor/imgui"
	include "core/vendor/tinygltf"
group ""

include "Core"
include "Project"

