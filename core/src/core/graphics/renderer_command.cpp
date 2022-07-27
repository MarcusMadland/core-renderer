#include "core/graphics/renderer_command.h"

#include "core/graphics/opengl/ogl_renderer_api.h"

namespace Core
{
	RendererAPI* RendererCommand::rendererAPI = new OpenGLRendererAPI;
}