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

// Libraries
#include <glad/glad.h>							// GLAD
#include <glm/glm.hpp>							// Math
#include <glm/gtc/type_ptr.hpp>					// Type Pointer
#include <glm/gtc/matrix_transform.hpp>			// Matrices math
#include <imgui.h>								// ImGui

using namespace Core;

// Logging
#define LOG_INFO(...) 		Logger::LOG(Logger::LogPriority::Info, (const char*)__VA_ARGS__);
#define LOG_WARN(...)		Logger::LOG(Logger::LogPriority::Warn, (const char*)__VA_ARGS__);
#define LOG_ERROR(...)		Logger::LOG(Logger::LogPriority::Error, (const char*)__VA_ARGS__);
#define LOG_CRITICAL(...)	Logger::LOG(Logger::LogPriority::Critical, (const char*)__VA_ARGS__);