/*
 * Copyright 2022 Marcus Madland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissionsand
 * limitations under the License.
 */

// "core-renderer", v2.0 WIP
// https://github.com/MarcusMadland/core-renderer

#pragma once

// Standard
#include <memory>

// Libraries
#include <imgui.h>

// Core
#include "core/input/keycodes.h"

// Version
#define CORE_VERSION		"2.0"
#define CORE_VERSION_NUM	 200

// Helper Macros

// Data Types
namespace Core
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}