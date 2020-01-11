#pragma once

#include "JuceHeader.h"
#include "CRemoteLoader.h"

class Injector// : private Timer
{
public:
	Injector();
	Injector(std::string nameIn);
	Injector(std::string nameIn, bool autoInjectIn, bool closeOnInjectIn);

	~Injector();

	Injector(Injector& other);

	BOOL CheckValidProcessExtension(const char* name);
	DWORD GetProcessId();
	void EnableDebugPriv() { Utils::SetDebugPrivilege(TRUE); };
	
	void SetProcessInformation(int processId)
	{ 
		processName = "League of Legends.exe"; 
		processId = processId; 
	}
	
	void SetDLLName(std::string dllname) { DLL = dllname; }
	void SetAutoInject(bool bAutoInj) { autoInject = bAutoInj; }
	void SetManualMap(bool bManualMap) { isManualMap = bManualMap; }
	void SetCloseOnInject(bool bCloseOnInj) { closeOnInject = bCloseOnInj; }

	void timerCallback();
	void beginTimer() { /*startTimer(750);*/ }
	void terminateTimer() { /*stopTimer();*/ }
	bool isTimerAlive() { return false;/* isTimerRunning();*/ }

	bool Setup();

	HRESULT ManualMap(std::string filePath);
	BOOL LoadLibraryInject(std::string filePath);

private:
	bool autoInject;
	bool closeOnInject;
	bool hasInjected;
	bool isManualMap;
	bool isReady;
	bool canInject;
	std::string DLL;
	std::vector<int> oldProcessIds;
	std::string processName;
	DWORD processId;
	HANDLE processHandle;
	CRemoteLoader remoteLoader;

	HMODULE hNtdll;
	tNTQSI fnQSI;
};