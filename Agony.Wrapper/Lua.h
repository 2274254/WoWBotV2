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
		generic<class T>
		static T Call(System::String^ code, ... array<System::Object^>^ variableArgs)
		{
			//auto test = System::Tuple::Create("dsad", 4234, 4234.423, "dsad");

			//auto result = Agony::Native::LuaFunctions::Call<std::tuple<T>>(msclr::interop::marshal_as<std::string>(code).c_str(), 231);

			return (T)0;
		}
	};
}