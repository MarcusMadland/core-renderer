#include "platform/windows/win_window.h"

namespace Core
{
	Window* Window::Create(const WindowInfo& info)
	{
		return new WindowsWindow(info);
	}
}