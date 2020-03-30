#pragma once
#include "CGObject.h"
#include <string>

namespace Agony
{
	namespace Native
	{
		class DLLEXPORT CGGameObject : public CGObject
		{
		public:
			bool Interact();
		};
	}
}