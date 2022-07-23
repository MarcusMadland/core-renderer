#include "core/layer/layerstack.h"

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