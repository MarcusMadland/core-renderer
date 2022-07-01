#include "ProjectLayer.h"

#include "core/app.h"

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
	std::unique_ptr<Project> app = std::make_unique<Project>();
	app->Run();
}