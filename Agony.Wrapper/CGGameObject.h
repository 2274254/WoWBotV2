#pragma once
#include "../Agony/CGGameObject.h"
#include "CGObject.h"

namespace Agony
{

	public ref class CGGameObject : public CGObject
	{
	internal:
		Native::CGGameObject* GetPtr();
	public:
		CGGameObject(Native::CGGameObject* obj) : CGObject(obj) {}
		bool Interact();
	};
}