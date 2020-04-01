#pragma once
#include "CGGameObject.h"

namespace Agony
{
	public ref class ObjectManager
	{
	public:
		static System::Collections::Generic::List<CGGameObject^>^ GetGameObjectsVisible();
		static System::Collections::Generic::List<CGGameObject^>^ GetGameObjects();
	};
}
