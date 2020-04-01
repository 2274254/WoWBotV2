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
			System::Console::WriteLine("About to call Native Interact");
			return this->GetPtr()->Interact();
		}
		System::Console::WriteLine("GameObject PTR is NULLPTR");
		return false;
	}
}