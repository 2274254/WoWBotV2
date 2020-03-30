#include "CGGameObject.h"

namespace Agony
{
	Native::CGGameObject* CGGameObject::GetPtr()
	{
		return this->self;
	}

	CGGameObject::CGGameObject(Native::CGGameObject* obj)
	{
		this->self = obj;
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