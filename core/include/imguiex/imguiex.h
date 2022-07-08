#pragma once

#include <iostream>

#include <imgui.h>

#include "core/app.h"

namespace ImGuiEx
{
	static void ShowFPS()
		{
			// Set window pos to be closer to the edge
			ImGui::SetNextWindowPos( { ImGui::GetWindowPos().x - 50,
				ImGui::GetWindowPos().y - 50 } );
			ImGui::SetNextWindowSize({ 200, 200 });

			// Begin FPS window with flags to hide bunch of imgui stuff
			ImGui::Begin("FPS", (bool*)0, ImGuiWindowFlags_NoTitleBar
				| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
				| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings
				| ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);

			ImGui::Text("FRAME: %.2f FPS",				// FPS
				ImGui::GetIO().Framerate);
			ImGui::Text("TIME: %.2f ms",				// MS
				1000.0f / ImGui::GetIO().Framerate);
			ImGui::Text("DRAWCALLS: %s",				// DRAWCALLS
				0);		
			ImGui::Text("VERTS: &s",					// VERTICES
				0);										

			ImGui::End();
		}
}