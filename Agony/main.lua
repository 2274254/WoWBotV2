-- MAIN_CODE R"lua(

print("Agony loaded");
AgonyCoreFrame = AgonyCoreFrame or CreateFrame("Frame")
AgonyCoreFrame:RegisterEvent("GOSSIP_SHOW")
AgonyCoreFrame:RegisterEvent("CINEMATIC_START")
AgonyCoreFrame:RegisterEvent("CINEMATIC_STOP")

AgonyCoreFrame:RegisterEvent("PLAYER_MOUNT_DISPLAY_CHANGED")
AgonyCoreFrame:RegisterEvent("UNIT_MODEL_CHANGED")
AgonyCoreFrame:RegisterEvent("PLAYER_EQUIPMENT_CHANGED")
AgonyCoreFrame:RegisterEvent("LOADING_SCREEN_DISABLED")
AgonyCoreFrame:RegisterEvent("UPDATE_SHAPESHIFT_FORM")
AgonyCoreFrame:RegisterEvent("UNIT_PET")
AgonyCoreFrame:RegisterEvent("COMBAT_LOG_EVENT_UNFILTERED")
AgonyCoreFrame:RegisterEvent("PLAYER_STARTED_MOVING")
AgonyCoreFrame:RegisterEvent("PLAYER_STOPPED_MOVING")
AgonyCoreFrame:RegisterEvent("PLAYER_REGEN_DISABLED")
AgonyCoreFrame:RegisterEvent("PLAYER_REGEN_ENABLED")
AgonyCoreFrame:RegisterEvent("WORLD_STATE_TIMER_STOP")

AgonyCoreFrame:SetScript("OnEvent", function(self, event, ...)
	if event == "GOSSIP_SHOW"  then
		AgonyLuaEvents.OnGossipShow();
	elseif event == "CINEMATIC_START"  then
		local canCancel = ... --bad --cant have; here
		AgonyLuaEvents.OnCinematicStart(canCancel);
	elseif event == "CINEMATIC_STOP"  then
		AgonyLuaEvents.OnCinematicStop();
	elseif event == "PLAYER_STARTED_MOVING"  then
		AgonyLuaEvents.OnPlayerStartedMoving();
	elseif event == "PLAYER_STOPPED_MOVING"  then
		AgonyLuaEvents.OnPlayerStoppedMoving();
	end
	--print(event);
end)

-- )lua";