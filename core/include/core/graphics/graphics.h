#pragma once

namespace  Core
{
	class Graphics
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
