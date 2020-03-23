#pragma once
#include <windows.h>
#include <atlstr.h>
#include <vector>
#include "Macros.h"

namespace Agony
{
	public ref class Lua
	{
	internal:
	public:
		static Lua::Lua();

		static System::Collections::Generic::List<System::Object^>^ Call(System::String^ code, System::Collections::Generic::List<System::Int32>^ returns, ... array<System::Object^>^ variableArgs);
	};
}