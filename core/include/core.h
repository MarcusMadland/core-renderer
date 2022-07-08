#pragma once

// Main header file - include into application for complete access

// Core Renderer
#include "core/debug/logger/logger.h"			// Logging
#include "imguiex/imguiex.h"					// ImGui Extensions
#include "core/object/scene.h"					// Scene
#include "core/object/staticmesh.h"				// Object: StaticMesh
#include "core/object/importers/gltfimporter.h"	// Importer: FBX
#include "core/layerstack.h"					// Layers
#include "core/graphics/shader.h"				// Shader
#include "core/debug/logger/logger.h"			// Logger
#include "core/input/input.h"					// Input

// Libraries
#include <glad/glad.h>							// GLAD
#include <glm/glm.hpp>							// Math
#include <glm/gtc/type_ptr.hpp>					// Type Pointer
#include <glm/gtc/matrix_transform.hpp>			// Matrices math
#include <imgui.h>								// ImGui

using namespace Core;