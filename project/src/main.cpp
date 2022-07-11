#include "ProjectLayer.h"

#include "core/app.h"
#include "debug.h"

class Project : public Core::App
{
public:
	Project()
	{
		PushLayer(new ProjectLayer());
	}
};

int main()
{
	PROFILE_BEGIN_SESSION("Startup", "core-renderer-startup-profile.json");
	std::unique_ptr<Project> app = std::make_unique<Project>();
	PROFILE_END_SESSION();

	PROFILE_BEGIN_SESSION("Runtime", "core-renderer-runtime-profile.json");
	app->Run();
	PROFILE_END_SESSION();
}