-- MAIN_CODE R"lua(
--50.100.122.19:3389

print('|cFFDC143CAgony:|r |cFF40E0D0has been loaded.');
AgonyCoreFrame = AgonyCoreFrame or CreateFrame("Frame")
--AgonyCoreFrame:RegisterEvent("GOSSIP_SHOW")
AgonyCoreFrame:RegisterEvent("CINEMATIC_START")
AgonyCoreFrame:RegisterEvent("CINEMATIC_STOP")

--AgonyCoreFrame:RegisterEvent("PLAYER_MOUNT_DISPLAY_CHANGED")
--AgonyCoreFrame:RegisterEvent("UNIT_MODEL_CHANGED")
--AgonyCoreFrame:RegisterEvent("PLAYER_EQUIPMENT_CHANGED")
--AgonyCoreFrame:RegisterEvent("LOADING_SCREEN_DISABLED")
--AgonyCoreFrame:RegisterEvent("UPDATE_SHAPESHIFT_FORM")
--AgonyCoreFrame:RegisterEvent("UNIT_PET")
--AgonyCoreFrame:RegisterEvent("COMBAT_LOG_EVENT_UNFILTERED")
--AgonyCoreFrame:RegisterEvent("PLAYER_STARTED_MOVING")
--AgonyCoreFrame:RegisterEvent("PLAYER_STOPPED_MOVING")
--AgonyCoreFrame:RegisterEvent("PLAYER_REGEN_DISABLED")
--AgonyCoreFrame:RegisterEvent("PLAYER_REGEN_ENABLED")
--AgonyCoreFrame:RegisterEvent("WORLD_STATE_TIMER_STOP")

AgonyCoreFrame:SetScript("OnEvent", function(self, event, ...)
	AgonyLuaEvents.OnEvent(event, ...);
	--print(event);
end)

-- )lua";