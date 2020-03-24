#pragma once
#include "dxgi.h"

typedef HRESULT(__fastcall* D3D11Present) (IDXGISwapChain* pSwapChain, UINT syncInterval, UINT flags);
typedef HRESULT(__stdcall* D3D11ResizeBuffers) (IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

namespace Agony
{
	namespace Native
	{
		class D3dxHook
		{
			static D3D11Present Od11Present;
			static D3D11ResizeBuffers Od11ResizeBuffers;
			static bool initialised;
			static bool lastGameState;
		public:
			static bool ApplyHooks();
			static void ClearHooks();
			static HRESULT __fastcall HkPresentD11(IDXGISwapChain* pSwapChain, UINT syncInterval, UINT flags);
			static HRESULT __stdcall HkResizeBuffersD11(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
		};
	}
}