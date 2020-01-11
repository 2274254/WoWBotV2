#include "Game.h"
#include "Offsets.h"

std::string Agony::Native::Game::GetGameVersion()
{
	return *reinterpret_cast<std::string*>(Offsets::Base + Offsets::GameVersion);
}
