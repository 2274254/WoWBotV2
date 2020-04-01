#pragma once
#include <windows.h>
#include <memory>
#include <string>
#include "Macros.h"

#pragma comment(lib, "version.lib")

class DLLEXPORT BuildInfo
{
public:
	int32_t major;
	int32_t minor;
	int32_t bug_fix;
	int32_t build_number;

	BuildInfo()
	{
		CHAR dllPath[MAX_PATH] = { 0 };
		GetModuleFileName(GetModuleHandle(nullptr), dllPath, _countof(dllPath));
		DWORD  verHandle = 0;
		UINT   size = 0;
		LPBYTE lpBuffer = nullptr;
		const auto verSize = GetFileVersionInfoSize(dllPath, &verHandle);
		if (verSize)
		{
			const auto verData = std::make_unique<char[]>(verSize);

			if (GetFileVersionInfo(dllPath, verHandle, verSize, verData.get()) && VerQueryValue(verData.get(), "\\", reinterpret_cast<LPVOID*>(&lpBuffer), &size))
			{
				if (size)
				{
					const auto verInfo = reinterpret_cast<VS_FIXEDFILEINFO*>(lpBuffer);
					if (verInfo->dwSignature == 0xFEEF04BD)
					{
						major = static_cast<int32_t>(verInfo->dwFileVersionMS) >> 16 & 0xFFFF;
						minor = static_cast<int32_t>(verInfo->dwFileVersionMS) >> 0 & 0xFFFF;
						bug_fix = static_cast<int32_t>(verInfo->dwFileVersionLS) >> 16 & 0xFFFF;
						build_number = static_cast<int32_t>(verInfo->dwFileVersionLS) >> 0 & 0xFFFF;
					}
				}
			}
		}
	}

	[[nodiscard]] std::string ToString() const
	{
		return std::to_string(major) + "." + std::to_string(minor) + "." + std::to_string(bug_fix) + "." + std::to_string(build_number);
	}
};