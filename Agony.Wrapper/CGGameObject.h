#pragma once
#include "../Agony/CGGameObject.h"
#include "CGObject.h"

namespace Agony
{

	public ref class CGGameObject : public CGObject
	{
	internal:
		Native::CGGameObject* GetPtr();
	protected:
		Native::CGGameObject* self;
	public:
		CGGameObject(Native::CGGameObject* obj);
		CGGameObject() {};
		bool Interact();
	};
}