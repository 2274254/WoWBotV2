#pragma once

#include "JuceHeader.h"

class ProcessInfo //: public Component
{
public:
	ProcessInfo() : processName(""), processId(0)
	{
	}

	~ProcessInfo()
	{
		processId = NULL;
	}
	/*
	std::string toString()
	{
		std::string processText(processName);
		processText += "  ( ";
		processText += std::string((unsigned int)processId);
		processText += " )";
		return processText;
	}
	*/
	std::string processName;
	DWORD processId;
	/*
	class ProcessNameSorter
	{
	public:
		static int compareElements(ProcessInfo a, ProcessInfo b) {
			return a.processName.compareIgnoreCase(b.processName);
		}
	};
	*/
	class ProcessIdSorter
	{
	public:
		static int compareElements(ProcessInfo first, ProcessInfo second) {
			return (first.processId < second.processId) ? -1 : ((second.processId < first.processId) ? 1 : 0);
		}
	};

};