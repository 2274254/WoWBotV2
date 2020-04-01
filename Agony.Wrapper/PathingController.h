#pragma once
#include "../Agony/vector3.h"

namespace Agony
{
	public ref class PathingController
	{
		static float lastClickPositionX;
		static float lastClickPositionY;
		static float lastClickPositionZ;
	public:
		static void ClickToMove(float x, float y, float z);
		static System::Collections::Generic::List<SharpDX::Vector3>^ CalculatePath(int instanceId, SharpDX::Vector3 from, SharpDX::Vector3 to);
		static void MoveTo(float x, float y, float z);
		static void Reset();
	};
}