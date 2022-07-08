#include "core/object/object.h"

namespace Core
{
	void Object::SetObjectPosition(glm::vec3 newPos)
	{
		pos = newPos;
	}
	void Object::SetObjectRotation(glm::vec3 newRot)
	{
		eulerRot = newRot;
	}
	void Object::SetObjectScale(glm::vec3 newScale)
	{
		scale = newScale;
	}
	void Object::AddChild(Object* child)
	{
		children.push_back(child);
	}
	glm::mat4 Object::GetLocalModelMatrix()
	{
		const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
			glm::radians(eulerRot.x),
			glm::vec3(1.0f, 0.0f, 0.0f));

		const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
			glm::radians(eulerRot.y),
			glm::vec3(0.0f, 1.0f, 0.0f));

		const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
			glm::radians(eulerRot.z),
			glm::vec3(0.0f, 0.0f, 1.0f));

		const glm::mat4 roationMatrix =
			transformY * transformX * transformZ;

		// Position * Rotation * Scale
		glm::mat4 modelMat = glm::mat4(1.0f);

		glm::mat4 positionMat = glm::translate(glm::mat4(1.0f), pos);
		glm::mat4 rotMat = roationMatrix;
		glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);

		modelMat = positionMat * rotMat * scaleMat;

		return modelMat;

	}
}