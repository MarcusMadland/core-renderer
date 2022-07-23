#include "platform/windows/winwindow.h"

namespace Core
{
	Window* Window::Create(const WindowInfo& info)
	{
		return new WindowsWindow(info);
	}
}