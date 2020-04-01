#include "CGGameObject.h"

namespace Agony
{
	Native::CGGameObject* CGGameObject::GetPtr()
	{
		return static_cast<Native::CGGameObject*>(this->self);
	}

	bool CGGameObject::Interact()
	{
		auto gameObject = this->GetPtr();
		if (gameObject != nullptr)
		{
			return this->GetPtr()->Interact();
		}
		return false;
	}
}