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

#include "core/layer/layer_stack.h"

namespace Core
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (uint32_t i = 0; i < layers.size(); i++)
			delete layers[i];
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layers.emplace(layers.begin() + layerInsertIndex, layer);
		layerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(layers.begin(), layers.begin()
			+ layerInsertIndex, layer);

		if (it != layers.begin() + layerInsertIndex)
		{
			layer->OnDetach();
			layers.erase(it);
			layerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(layers.begin() + layerInsertIndex,
			layers.end(), overlay);

		if (it != layers.end())
		{
			overlay->OnDetach();
			layers.erase(it);
		}
	}
}