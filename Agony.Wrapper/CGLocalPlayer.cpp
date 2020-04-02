#include "CGLocalPlayer.h"

namespace Agony
{
	Native::CGLocalPlayer* CGLocalPlayer::GetPtr()
	{
		return static_cast<Native::CGLocalPlayer*>(this->self);
	}

	Int32 CGLocalPlayer::Money::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetMoney();
		}
		return 0;
	}

	Int32 CGLocalPlayer::CurrentXP::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetCurrentXP();
		}
		return 0;
	}

	Int32 CGLocalPlayer::MaxXP::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetMaxXP();
		}
		return 0;
	}

	void CGLocalPlayer::RepopMe()
	{
		auto player = this->GetPtr();
		if (player != nullptr)
		{
			player->RepopMe();
		}
	}

	void CGLocalPlayer::RetrieveCorpse()
	{
		auto player = this->GetPtr();
		if (player != nullptr)
		{
			player->RetrieveCorpse();
		}
	}
}