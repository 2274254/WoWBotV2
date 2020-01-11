#include "Game.h"
#include "Offsets.h"
#include "Macros.h"
#include <iostream>

bool Agony::Native::Game::IsInGame()
{
	IS_NULL_RETN(Offsets::Base, static_cast<int>(Offsets::InGame), false);
	const int16_t gameState = *reinterpret_cast<int16_t*>(Offsets::Base + Offsets::InGame);
	return ((gameState >> 4) & 1);
}

char* Agony::Native::Game::GetGameVersion()
{
	IS_NULL_RETN(Offsets::Base, static_cast<int>(Offsets::GameVersion), "Unknown");
	return reinterpret_cast<char*>(Offsets::Base + static_cast<int>(Offsets::GameVersion));
}
