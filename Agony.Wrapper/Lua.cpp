#include "Lua.h"
#include "../Agony/LuaFunctions.h"
#include <msclr\marshal_cppstd.h>

namespace Agony
{
	static Lua::Lua()
	{
	}
	System::Collections::Generic::List<System::Object^>^ Lua::Call(System::String^ code, System::Collections::Generic::List<System::Int32>^ returns, ... array<System::Object^>^ variableArgs)
	{
		std::vector<int> returnsUnmanaged;
		for each (int expectedReturn in returns)
		{
			returnsUnmanaged.push_back(expectedReturn);
		}

		auto result = Agony::Native::LuaFunctions::Call(msclr::interop::marshal_as<std::string>(code).c_str(), returnsUnmanaged, "player");//TODO

		System::Collections::Generic::List<System::Object^>^ returnValues = gcnew System::Collections::Generic::List<System::Object^>();

		int i = 0;
		for each (int expectedReturn in returns)
		{
			if (expectedReturn == 0)
			{
				returnValues->Add(gcnew System::Boolean(std::any_cast<bool>(result[i])));
			}
			else if (expectedReturn == 1)
			{
				returnValues->Add(gcnew System::Double(std::any_cast<double>(result[i])));
			}
			else if (expectedReturn == 3)
			{
				returnValues->Add(gcnew System::String(std::any_cast<char*>(result[i])));
			}
			i++;
		}

		return returnValues;
	}
}