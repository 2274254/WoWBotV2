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
		std::string functionName = msclr::interop::marshal_as<std::string>(code);

		std::vector<int> returnsUnmanaged;
		for each (int expectedReturn in returns)
		{
			returnsUnmanaged.push_back(expectedReturn);
		}

		auto result = Agony::Native::LuaFunctions::Call(functionName, returnsUnmanaged, 5);//TODO

		System::Collections::Generic::List<System::Object^>^ returnValues = gcnew System::Collections::Generic::List<System::Object^>();

		int i = 0;
		for (unsigned i = 0; i < result.size(); i++)
		{
			auto returnValue	= result[i];
			auto expectedReturn = returns[i];
			if (expectedReturn == 0)
			{
				returnValues->Add(gcnew System::Boolean(std::any_cast<bool>(returnValue)));
			}
			else if (expectedReturn == 1)
			{
				returnValues->Add(gcnew System::Double(std::any_cast<double>(returnValue)));
			}
			else if (expectedReturn == 3)
			{
				returnValues->Add(gcnew System::String(std::any_cast<char*>(returnValue)));
			}
		}
		return returnValues;
	}
}