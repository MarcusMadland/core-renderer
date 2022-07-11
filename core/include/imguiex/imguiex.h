#pragma once

#include <iostream>

#include <imgui.h>

#include "core/app.h"
#include "debug.h"

namespace ImGuiEx
{
	static void ShowFPS()
	{
		PROFILE_SCOPE("ImGuiEx");

		auto& results = Core::App::Instance().GetTimerResults();

		// Set window pos to be closer to the edge
		ImGui::SetNextWindowPos({ ImGui::GetWindowPos().x - 50,
			ImGui::GetWindowPos().y - 50 });
		ImGui::SetNextWindowSize({ 300, 300 });

		// Performance Titles
		ImGui::Begin("Performance Titles", (bool*)0, ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings
			| ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);

		// FRAME TIME TIMERS LABELS
		for (auto& result : results)
		{
			char label[50];
			strcpy_s(label, result.name);
			strcat_s(label, "");
			ImGui::Text(label, result.time);
		}

		ImGui::Text("framerate: ");
		ImGui::Text("drawcalls: ");
		ImGui::Text("vertices: ");
		ImGui::Text("triangels: ");
	
		ImGui::End();

		// Set window pos to be closer to the edge
		ImGui::SetNextWindowPos({ ImGui::GetWindowPos().x + 50,
			ImGui::GetWindowPos().y - 50 });
		ImGui::SetNextWindowSize({ 300, 300 });

		ImGui::Begin("Performance", (bool*)0, ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings
			| ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);

		// FRAME TIME TIMERS
		for (auto& result : results)
		{
			char label[50];
			strcpy_s(label, "");
			strcat_s(label, "%.2f ms");

			if (result.time >= 16.7f)
				ImGui::PushStyleColor(ImGuiCol_Text, { 1.0f, 0.0f, 0.0f, 1.0f });
			else
				ImGui::PushStyleColor(ImGuiCol_Text, { 0.0f, 1.0f, 0.0f, 1.0f });

			ImGui::Text(label, result.time);

			ImGui::PopStyleColor();
		}
		results.clear();

		// FRAME RATE (FPS)
		{
			if (ImGui::GetIO().Framerate <= 60.0f)
				ImGui::PushStyleColor(ImGuiCol_Text, { 1.0f, 0.0f, 0.0f, 1.0f });
			else
				ImGui::PushStyleColor(ImGuiCol_Text, { 0.0f, 1.0f, 0.0f, 1.0f });
		
			ImGui::Text("%.2f fps", ImGui::GetIO().Framerate);

			ImGui::PopStyleColor();
		}

		// DRAW CALLS
		{
			uint32_t draws = Core::App::Instance().GetDrawCalls();
			Core::App::Instance().ResetDrawCalls();

			if (draws >= 2000)
				ImGui::PushStyleColor(ImGuiCol_Text, { 1.0f, 0.0f, 0.0f, 1.0f });
			else
				ImGui::PushStyleColor(ImGuiCol_Text, { 0.0f, 1.0f, 0.0f, 1.0f });

			ImGui::Text("%u", draws);

			ImGui::PopStyleColor();
		}

		// VERTICES
		uint32_t verts = Core::App::Instance().GetVertCount();
		Core::App::Instance().ResetVertCount();
		ImGui::Text("%u", verts);

		// TRIANGLES
		ImGui::Text("%u",
			verts / 3);

		ImGui::End();
	}
}