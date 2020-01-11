#include "Drawings.h"
#include "Camera.h"
#include "Offsets.h"

#include <D3DX11.h>
#include <DirectXMath.h>
#include <iostream>

ID3D11Device* Drawings::pDevice = nullptr;
ID3D11DeviceContext* Drawings::pDeviceContext = nullptr;
ID3D11RenderTargetView* Drawings::RenderTargetView = nullptr;
ID3D11RenderTargetView* Drawings::NormalTargetView = nullptr;;
Vector3* Drawings::Waypoints = nullptr;
int Drawings::WaypointsLenght = 0;
int Drawings::CurrentWaypoint = 0;

BigVector2 Drawings::WorldToScreen(Vector3 unitPosition)
{
	const auto Deg2Rad = 0.0174532925f;
	const auto pCameraBase = *reinterpret_cast<CameraBase**>(Offsets::Base + Offsets::CameraBase);
	auto pCamera = pCameraBase->camera_ptr;

	ImGuiIO& io = ImGui::GetIO();
	
	//auto cam = m.read<CCamera>(pCamera);
	RECT rc = { 0,0,io.DisplaySize.x,io.DisplaySize.y };
	BigVector3 difference{ unitPosition.x - pCamera->pos.x, unitPosition.y - pCamera->pos.y, unitPosition.z - pCamera->pos.z };
	
	double product =
		difference.x * pCamera->mat.M11 +
		difference.y * pCamera->mat.M12 +
		difference.z * pCamera->mat.M13;

	if (product < 0)
		return BigVector2{ 0,0 };

	Matrix3x3 inverse = pCamera->mat.Inverse();	

	BigVector3 view{
		inverse.M11 * difference.x + inverse.M21 * difference.y + inverse.M31 * difference.z ,
		inverse.M12 * difference.x + inverse.M22 * difference.y + inverse.M32 * difference.z,
		inverse.M13 * difference.x + inverse.M23 * difference.y + inverse.M33 * difference.z
	};
	BigVector3 camera{ -view.y, -view.z, view.x };
	BigVector2 gameScreen{ (rc.right - rc.left) / 2.0f , (rc.bottom - rc.top) / 2.0f };
	BigVector2 aspect{ gameScreen.x / tan(((pCamera->fov * 55.0f) / 2.0f) * Deg2Rad) ,gameScreen.y / tan(((pCamera->fov * 35.0f) / 2.0f) * Deg2Rad) };
	BigVector2 screenPos{ gameScreen.x + camera.x * aspect.x / camera.z,gameScreen.y + camera.y * aspect.y / camera.z };

//	if (screenPos.x < 0 || screenPos.y < 0 || screenPos.x > rc.right || screenPos.y > rc.bottom)
//		return Vector2{ 0,0 };

	if (product < 0.98f)
	{
		screenPos.x *= 1 + product;
		screenPos.y *= 1 + product;
	}

	return screenPos;
}

bool Drawings::WorldToScreen(Vector3 worldPos, Vector2* output)
{
	CameraBase* pCameraBase = *reinterpret_cast<CameraBase**>(Offsets::Base + Offsets::CameraBase);
	if (pCameraBase == nullptr || pCameraBase->camera_ptr == nullptr) return false;
	ImGuiIO& io = ImGui::GetIO();

	float nearClip = 1.0f;
	float farClip = 10000.0f;

	//Get Projection Matrix
	float fAspect = ((float)io.DisplaySize.x) / io.DisplaySize.y;	
	DirectX::XMMATRIX Proj = DirectX::XMMatrixPerspectiveFovRH(pCameraBase->camera_ptr->fov * 0.6, fAspect, nearClip, farClip);

	//Get View Matrix
	DirectX::XMFLOAT3 vEyePt(pCameraBase->camera_ptr->pos.x, pCameraBase->camera_ptr->pos.y, pCameraBase->camera_ptr->pos.z);
	DirectX::XMFLOAT3 vLookatPt(pCameraBase->camera_ptr->pos.x + pCameraBase->camera_ptr->mat.M11, pCameraBase->camera_ptr->pos.y + pCameraBase->camera_ptr->mat.M12, pCameraBase->camera_ptr->pos.z + pCameraBase->camera_ptr->mat.M13);
	DirectX::XMFLOAT3 vUpVec(0.0f, 0.0f, 1.0f);
	DirectX::XMMATRIX View = DirectX::XMMatrixLookAtRH(DirectX::XMLoadFloat3(&vEyePt), DirectX::XMLoadFloat3(&vLookatPt), DirectX::XMLoadFloat3(&vUpVec));
	
	//Project our position
	auto inPos = DirectX::XMFLOAT3(worldPos.x, worldPos.y, worldPos.z);
	auto outVect = DirectX::XMVector3Project(DirectX::XMLoadFloat3(&inPos), 0, 0, io.DisplaySize.x, io.DisplaySize.y, nearClip, farClip, Proj, View, DirectX::XMMatrixIdentity());
	
	output->x = DirectX::XMVectorGetX(outVect);
	output->y = DirectX::XMVectorGetY(outVect);

	return (DirectX::XMVectorGetZ(outVect) > 0.f );
}

void Drawings::DrawLine(Vector2 from, Vector2 to)
{
	/*
	if (m_pDx11Renderer)
	{
		m_pDx11Renderer->Initialize();
		Color xcolor = Color(255, 25, 180, 255);
		long size = 8, strong = 1;
		m_pDx11Renderer->DrawLine(from.x, from.y, to.x, to.y, xcolor);
	}*/
}

void Drawings::DrawLine(Vector3 from, Vector3 to)
{
	//DrawLine(WorldToScreen(from), WorldToScreen(to));
}