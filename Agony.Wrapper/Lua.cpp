#include "Lua.h"
#include "../Agony/LuaFunctions.h"
#include <msclr\marshal_cppstd.h>

namespace Agony
{
	static Lua::Lua()
	{
	}

	System::Collections::Generic::List<System::Object^>^ Call(System::String^ code, System::Collections::Generic::List<System::String^>^ returns, ... array<System::Object^>^ variableArgs)
	{
		std::vector<std::string> expectedReturns;
		for each (auto expectedReturn in returns)
		{
			expectedReturns.push_back(msclr::interop::marshal_as<std::string>(expectedReturn));
		}

		auto result = Agony::Native::LuaFunctions::Call(msclr::interop::marshal_as<std::string>(code).c_str(), expectedReturns, 231);
		System::Collections::Generic::List<System::Object^>^ returnValues = gcnew System::Collections::Generic::List<System::Object^>();

		for (unsigned i = 0; i < result.size(); i++)
		{
			if (expectedReturns[i] == "string") returnValues->Add(gcnew System::String(std::any_cast<std::string>(result[i]).c_str()));
		}

		return returnValues;
	}
}