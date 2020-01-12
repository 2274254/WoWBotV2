#pragma once
#include <metahost.h>
#include <mscoree.h>
#include <stdio.h>
#include <direct.h>
#pragma comment(lib, "mscoree.lib")
#include "Utils.h"

enum class BootstrapEventType
{
	Load
};

namespace Agony
{
	namespace Native
	{
		#pragma pack(push, 1)
		typedef struct
		{
			wchar_t SandboxDllPath[256];
			wchar_t WrapperDllPath[256];
			wchar_t CoreDllPath[256];
			wchar_t Hash[128];
		} BootstrapMemoryLayout;
		#pragma pack(pop)

		class Bootstrapper
		{
		private:
			ICLRMetaHost* pMetaHost = nullptr;
			ICLRRuntimeHost* pRuntimeHost = nullptr;
			ICLRRuntimeInfo* pRuntimeInfo = nullptr;
			BootstrapMemoryLayout* m_bsMemoryLayout;

			bool m_isFallback;
		public:
			static Bootstrapper* GetInstance();

			bool Initialize();
			bool HostClr();
			bool InjectWrapper();
			bool LoadSandbox();
			bool LoadMemoryLayout();

			static void Trigger(BootstrapEventType eventType);

			BootstrapMemoryLayout* GetMemoryLayout();
			void SetMemoryLayout(BootstrapMemoryLayout* layout);
		};
	}
}