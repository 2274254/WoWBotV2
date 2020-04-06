#pragma once
#include "EventHandler.h"
#include <string>

namespace Agony::Native::LuaEvents
{
	class C_AchievementInfo
	{
	public:
		EventHandler<void(int, bool), int, bool> ACHIEVEMENT_EARNED = EventHandler<void(int, bool), int, bool>();
		EventHandler<void(int), int> ACHIEVEMENT_PLAYER_NAME = EventHandler<void(int), int>();
		EventHandler<void()> ACHIEVEMENT_SEARCH_UPDATED = EventHandler<void()>();
		EventHandler<void(int), int> CRITERIA_COMPLETE = EventHandler<void(int), int>();
		EventHandler<void(int, std::string), int, std::string> CRITERIA_EARNED = EventHandler<void(int, std::string), int, std::string>();
		EventHandler<void()> CRITERIA_UPDATE = EventHandler<void()>();
		EventHandler<void(std::string), std::string> INSPECT_ACHIEVEMENT_READY = EventHandler<void(std::string), std::string>();
		EventHandler<void()> RECEIVED_ACHIEVEMENT_LIST = EventHandler<void()>();
		EventHandler<void(int), int> RECEIVED_ACHIEVEMENT_MEMBER_LIST = EventHandler<void(int), int>();
		EventHandler<void(int, bool), int, bool> TRACKED_ACHIEVEMENT_LIST_CHANGED = EventHandler<void(int, bool), int, bool>();
		EventHandler<void(int, int, int, int), int, int, int, int> TRACKED_ACHIEVEMENT_UPDATE = EventHandler<void(int, int, int, int), int, int, int, int>();
	};

	class C_ActionBar
	{
	public:
		EventHandler<void()> ACTIONBAR_HIDEGRID = EventHandler<void()>();
		EventHandler<void()> ACTIONBAR_PAGE_CHANGED = EventHandler<void()>();
		EventHandler<void()> ACTIONBAR_SHOW_BOTTOMLEFT = EventHandler<void()>();
		EventHandler<void()> ACTIONBAR_SHOWGRID = EventHandler<void()>();
		EventHandler<void(int), int> ACTIONBAR_SLOT_CHANGED = EventHandler<void(int), int>();
		EventHandler<void()> ACTIONBAR_UPDATE_COOLDOWN = EventHandler<void()>();
		EventHandler<void()> ACTIONBAR_UPDATE_STATE = EventHandler<void()>();
		EventHandler<void()> ACTIONBAR_UPDATE_USABLE = EventHandler<void()>();
		EventHandler<void()> PET_BAR_UPDATE = EventHandler<void()>();
		EventHandler<void()> UPDATE_BONUS_ACTIONBAR = EventHandler<void()>();
		EventHandler<void()> UPDATE_EXTRA_ACTIONBAR = EventHandler<void()>();
		EventHandler<void()> UPDATE_MULTI_CAST_ACTIONBAR = EventHandler<void()>();
		EventHandler<void()> UPDATE_OVERRIDE_ACTIONBAR = EventHandler<void()>();
	};

	class C_AddOns
	{
	public:
		EventHandler<void(std::string), std::string> ADDON_LOADED = EventHandler<void(std::string), std::string>();
		EventHandler<void(bool), bool> ADDONS_UNLOADING = EventHandler<void(bool), bool>();
		EventHandler<void(std::string), std::string> SAVED_VARIABLES_TOO_LARGE = EventHandler<void(std::string), std::string>();
	};

	class C_AdventureJournal
	{
	public:
		EventHandler<void(int), int> AJ_DUNGEON_ACTION = EventHandler<void(int), int>();
		EventHandler<void()> AJ_OPEN = EventHandler<void()>();
		EventHandler<void()> AJ_PVE_LFG_ACTION = EventHandler<void()>();
		EventHandler<void(int), int> AJ_PVP_ACTION = EventHandler<void(int), int>();
		EventHandler<void()> AJ_PVP_LFG_ACTION = EventHandler<void()>();
		EventHandler<void()> AJ_PVP_RBG_ACTION = EventHandler<void()>();
		EventHandler<void()> AJ_PVP_SKIRMISH_ACTION = EventHandler<void()>();
		EventHandler<void(int, int), int, int> AJ_QUEST_LOG_OPEN = EventHandler<void(int, int), int, int>();
		EventHandler<void(int), int> AJ_RAID_ACTION = EventHandler<void(int), int>();
		EventHandler<void()> AJ_REFRESH_DISPLAY = EventHandler<void()>();
		EventHandler<void()> AJ_REWARD_DATA_RECEIVED = EventHandler<void()>();
	};

	class C_AdventureMap
	{
	public:
		EventHandler<void()> ADVENTURE_MAP_CLOSE = EventHandler<void()>();
		EventHandler<void(int), int> ADVENTURE_MAP_OPEN = EventHandler<void(int), int>();
		EventHandler<void(int), int> ADVENTURE_MAP_QUEST_UPDATE = EventHandler<void(int), int>();
		EventHandler<void()> ADVENTURE_MAP_UPDATE_INSETS = EventHandler<void()>();
		EventHandler<void()> ADVENTURE_MAP_UPDATE_POIS = EventHandler<void()>();
	};

	class C_AlliedRaces
	{
	public:
		EventHandler<void()> ALLIED_RACE_CLOSE = EventHandler<void()>();
		EventHandler<void(int), int> ALLIED_RACE_OPEN = EventHandler<void(int), int>();
	};

	class C_AreaPoiInfo
	{
	public:
		EventHandler<void()> AREA_POIS_UPDATED = EventHandler<void()>();
	};

	class C_ArtifactUI
	{
	public:
		EventHandler<void()> ARTIFACT_CLOSE = EventHandler<void()>();
		EventHandler<void(int, int, int, int), int, int, int, int> ARTIFACT_ENDGAME_REFUND = EventHandler<void(int, int, int, int), int, int, int, int>();
		EventHandler<void()> ARTIFACT_RELIC_FORGE_CLOSE = EventHandler<void()>();
		EventHandler<void()> ARTIFACT_RELIC_FORGE_PREVIEW_RELIC_CHANGED = EventHandler<void()>();
		EventHandler<void()> ARTIFACT_RELIC_FORGE_UPDATE = EventHandler<void()>();
		EventHandler<void()> ARTIFACT_RELIC_INFO_RECEIVED = EventHandler<void()>();
		EventHandler<void()> ARTIFACT_RESPEC_PROMPT = EventHandler<void()>();
		EventHandler<void(int, int, int), int, int, int> ARTIFACT_TIER_CHANGED = EventHandler<void(int, int, int), int, int, int>();
		EventHandler<void(bool), bool> ARTIFACT_UPDATE = EventHandler<void(bool), bool>();
		EventHandler<void()> ARTIFACT_XP_UPDATE = EventHandler<void()>();
	};






	class C_GossipInfo
	{
	public:
		EventHandler<void()> GOSSIP_SHOW = EventHandler<void()>();
	};
}