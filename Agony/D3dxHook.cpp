#include "D3dxHook.h"
#include "kiero.h"
#include "Drawings.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "LuaFunctions.h"
#include "Offsets.h"
#include "Core.h"
#include "Game.h"
#include "ObjectManager.h"
#include <iostream>

namespace Agony
{
	namespace Native
	{
		D3D11Present D3dxHook::Od11Present = nullptr;
		D3D11ResizeBuffers D3dxHook::Od11ResizeBuffers = nullptr;
		bool D3dxHook::initialised		= false;
		bool D3dxHook::lastGameState	= false;

		bool D3dxHook::ApplyHooks()
		{
			if (init(kiero::RenderType::D3D11) == kiero::Status::Success && kiero::bind(8, reinterpret_cast<void**>(&Od11Present), static_cast<void*>(HkPresentD11)) == kiero::Status::Success)
			{
				printf("Successfully hooked dxd11!\n");
				if (kiero::bind(13, reinterpret_cast<void**>(&Od11ResizeBuffers), static_cast<void*>(HkResizeBuffersD11)) == kiero::Status::Success)
				{
					//SUCCESS
				}
				else
				{
					printf("Failed to hook dxd11 resize buffers");
					ClearHooks();
					return false;
				}
			}
			else
			{
				printf("Failed to hook dxd11 present");
				return false;
			}
			return true;
		}

		void D3dxHook::ClearHooks()
		{
			kiero::shutdown();
		}

		HRESULT __fastcall D3dxHook::HkPresentD11(IDXGISwapChain* pSwapChain, UINT syncInterval, UINT flags)
		{
			if (!initialised)
			{
				initialised = true;

				pSwapChain->GetDevice(__uuidof(Drawings::pDevice), (void**)&Drawings::pDevice);
				Drawings::pDevice->GetImmediateContext(&Drawings::pDeviceContext);

				// Setup Dear ImGui context
				IMGUI_CHECKVERSION();
				ImGui::CreateContext();

				ImGuiIO& io = ImGui::GetIO();
				io.MouseDrawCursor = false;
				io.DeltaTime = 1.0f / 60.0f;
				io.Fonts->AddFontDefault();

				//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
				//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

				// Setup Dear ImGui style
				//ImGui::StyleColorsDark();
				//ImGui::StyleColorsClassic();

				/*ID3D11Texture2D* pBackBuffer;
				pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
				Drawings::pDevice->CreateRenderTargetView(pBackBuffer, NULL, &Drawings::pRenderTarget);
				pBackBuffer->Release();*/

				// Setup Platform/Renderer bindings
				ImGui_ImplWin32_Init(Core::MainWindowHandle);
				ImGui_ImplDX11_Init(Drawings::pDevice, Drawings::pDeviceContext);
				ImGui_ImplDX11_CreateDeviceObjects();
			}
			
			static ID3D11DepthStencilView* NormalDepthStencil;
			static D3D11_VIEWPORT viewport;

			ImGuiIO& io = ImGui::GetIO();

			if (Drawings::RenderTargetView == nullptr)
			{
				//viewport
				UINT vps = 1;
				Drawings::pDeviceContext->RSGetViewports(&vps, &viewport);
				//get backbuffer
				ID3D11Texture2D* backbuffer = nullptr;
				HRESULT hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&backbuffer));
				if (FAILED(hr))
				{
					Drawings::pDeviceContext->OMGetRenderTargets(1, &Drawings::RenderTargetView, nullptr);
					Drawings::pDeviceContext->OMSetRenderTargets(1, &Drawings::RenderTargetView, nullptr);
					return hr;
				}
				//create rendertarget
				hr = Drawings::pDevice->CreateRenderTargetView(backbuffer, nullptr, &Drawings::RenderTargetView);
				backbuffer->Release();
				if (FAILED(hr))
				{
					return hr;
				}
			}
			else
			{
				//Drawings::pDeviceContext->AddRef();

				D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
				depthStencilDesc.DepthEnable = TRUE;
				depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
				depthStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
				depthStencilDesc.StencilEnable = FALSE;
				depthStencilDesc.StencilReadMask = 0xFF;
				depthStencilDesc.StencilWriteMask = 0xFF;

				// Stencil operations if pixel is front-facing
				depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
				depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

				// Stencil operations if pixel is back-facing
				depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
				depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
				depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
				ID3D11Texture2D* m_depthStencilBuffer = nullptr;
				D3D11_DEPTH_STENCIL_VIEW_DESC* m_DepthStencilViewDesc = nullptr;
				ID3D11DepthStencilState* m_DepthStencilState = nullptr;
				ID3D11DepthStencilView* m_DepthStencilView = nullptr;
				Drawings::pDevice->CreateDepthStencilState(&depthStencilDesc, &m_DepthStencilState);
				Drawings::pDeviceContext->OMSetDepthStencilState(m_DepthStencilState, 0);
				Drawings::pDevice->CreateDepthStencilView(m_depthStencilBuffer, m_DepthStencilViewDesc, &m_DepthStencilView); //try this probably not it though

				Drawings::pDeviceContext->OMGetRenderTargets(1, &Drawings::NormalTargetView, &NormalDepthStencil);
				Drawings::pDeviceContext->OMSetRenderTargets(1, &Drawings::RenderTargetView, m_DepthStencilView);

				//check if in game if not set we need to re register,
				//if we are in game and need to re regiser, then reregister, ez pz :P
				auto isInGame = Agony::Native::Game::IsInGame();
				if (isInGame)
				{
					if (lastGameState == false)
					{
						std::cout << "Game state changed" << std::endl;
						for (const auto function : Agony::Native::LuaFunctions::FunctionsMap)
						{
							if (Agony::Native::LuaFunctions::FramescriptRegister(function.first, function.second))
							{
								printf("Registered %s\n", function.first);
							}
						}

						//std::string result = Agony::Native::LuaFunctions::ExecuteGetResult("globalVar = GetUnitPosition('player')", "globalVar");
						/*auto ret = Agony::Native::LuaFunctions::Call("GetUnitPosition", { 1, 1, 1 }, "player");
						if (ret.size() == 3)
						{
							std::cout << "Player Pos = " << std::any_cast<double>(ret[0]) << ", " << std::any_cast<double>(ret[1]) << ", " << std::any_cast<double>(ret[2]) << std::endl;
						}*/

						//
						/*
						WoWObject* me = Agony::Native::Game::Me();
						std::cout << "Local player class " << (int)me->unitClass << std::endl;
						std::cout << "Local player race " << (int)me->unitRace << std::endl;
						std::cout << "Local player address 0x" << std::hex << me << std::endl;*/

						//int health = *(int*)(me + 0x1580);
						//std::cout << "Player Health = " << health << std::endl;

						ObjectManager::GetVisibleObjects();


						//uintptr_t* objMgr = *(uintptr_t**)(Offsets::Base + Offsets::ObjectMgr);

						//uintptr_t* FirstObj = objMgr + 0x120;
					}
				}
				else
				{
					std::cout << "We are NOT ingame" << std::endl;
				}
				lastGameState = isInGame;

				ImGui_ImplDX11_NewFrame();
				ImGui_ImplWin32_NewFrame();

				ImGui::NewFrame();

				//ImGui::GetOverlayDrawList()->AddText(ImVec2(10, 10), 0xFF0000FF, "HELLO WORLD");
				//ImGui::GetOverlayDrawList()->AddLine(ImVec2(10, 10), ImVec2(300, 10), 0xFF0000FF);
				//const auto currentState = *reinterpret_cast<int16_t*>(Offsets::Base + Offsets::InGame);
				if (isInGame)
				{
					if (Drawings::Waypoints)
					{
						int pointsCount = 0;
						ImVec2* points = new ImVec2[Drawings::WaypointsLenght - Drawings::CurrentWaypoint + pointsCount];

						//Start at player
						//auto player = GetLocalPlayer();
						//auto playerScreenPos = Drawings::WorldToScreen(player->pos);
						//points[pointsCount] = ImVec2(playerScreenPos.x, playerScreenPos.y);

						//Add other points...
						for (int i = Drawings::CurrentWaypoint; i < Drawings::WaypointsLenght; i++)
						{
							Vector2 screenLoc;
							Drawings::WorldToScreen(Vector3(Drawings::Waypoints[i].x, Drawings::Waypoints[i].y, Drawings::Waypoints[i].z), &screenLoc);
							{
								points[pointsCount] = ImVec2(screenLoc.x, screenLoc.y);
								pointsCount++;
							}
							/*auto screenLoc = Drawings::WorldToScreen(Vector3(Drawings::Waypoints[i].x, Drawings::Waypoints[i].y, Drawings::Waypoints[i].z));
							if (screenLoc.x != 0 || screenLoc.y != 0)
							{
								if (i != Drawings::WaypointsLenght - 1)
								{
									auto nextScreenLoc = Drawings::WorldToScreen(Vector3(Drawings::Waypoints[i + 1].x, Drawings::Waypoints[i + 1].y, Drawings::Waypoints[i + 1].z));
									if (nextScreenLoc.x != 0 || nextScreenLoc.y != 0)
									{
										points[pointsCount] = ImVec2(screenLoc.x, screenLoc.y);
										pointsCount++;
									}
								}
								else
								{
									//Last point
									auto prevScreenLoc = Drawings::WorldToScreen(Vector3(Drawings::Waypoints[i - 1].x, Drawings::Waypoints[i - 1].y, Drawings::Waypoints[i - 1].z));
									if (prevScreenLoc.x != 0 || prevScreenLoc.y != 0)
									{
										points[pointsCount] = ImVec2(screenLoc.x, screenLoc.y);
										pointsCount++;
									}
								}
							}*/
						}

						if (pointsCount > 1)
						{
							ImVec2* realPoints = new ImVec2[pointsCount];
							memcpy(realPoints, points, pointsCount * sizeof(ImVec2));
							ImGui::GetOverlayDrawList()->AddPolyline(realPoints, Drawings::WaypointsLenght, 0xFF0000FF, false, 3);
						}
						delete[] points;
					}
				}

				ImGui::EndFrame();
				ImGui::Render();
				//Drawings::pDeviceContext->OMSetRenderTargets(1, &NormalTargetView, NormalDepthStencil);
				ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
			}
			return Od11Present(pSwapChain, syncInterval, flags);
		}

		HRESULT __stdcall D3dxHook::HkResizeBuffersD11(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
		{
			ImGui_ImplDX11_InvalidateDeviceObjects();
			if (Drawings::RenderTargetView != nullptr)
			{
				Drawings::RenderTargetView->Release();
				Drawings::RenderTargetView = nullptr;
			}
			return Od11ResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
		}
	}
}
