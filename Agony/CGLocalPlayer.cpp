#include "CGLocalPlayer.h"
#include "LuaFunctions.h"

void Agony::Native::CGLocalPlayer::RepopMe()
{
	if (IsDead() && !IsGhost())
	{
		LuaFunctions::Execute("RepopMe()");
	}
}

void Agony::Native::CGLocalPlayer::RetrieveCorpse()
{
	if (IsGhost())
	{
		LuaFunctions::Execute("RetrieveCorpse()");
	}
}
