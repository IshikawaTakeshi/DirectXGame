#pragma warning(push)
//C4023の警告を見なかったことにする
#pragma warning(disable:4023)

#include "WinApp.h"
#include "Logger.h"
#include "DirectXCommon.h"
#include "Transform.h"
#include "Texture.h"

#include <dxgidebug.h>
#pragma comment(lib,"dxguid.lib")

struct D3DResourceLeakChecker {
	~D3DResourceLeakChecker() {
		Microsoft::WRL::ComPtr<IDXGIDebug1> debug;
		if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug)))) {
			debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
			debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
			debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
		}
	}
};


//////////////////////////////////////////////////////////
//Windowsアプリでのエントリーポイント(main関数)
//////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	CoInitializeEx(0, COINIT_MULTITHREADED);

	D3DResourceLeakChecker leakCheck;

	WinApp* winApp = WinApp::GetInstance();
	winApp->Initialize();

	DirectXCommon* directXCommon = DirectXCommon::GetInstance();
	directXCommon->Initialize();

	Texture* texture = new Texture();
	texture->Initialize(directXCommon);

	Transform transform{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	Transform cameraTransform{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-5.0f} };
	Matrix4x4 worldMatrix = MatrixMath::MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);
	Matrix4x4 cameraMatrix = MatrixMath::MakeAffineMatrix(
		cameraTransform.scale,cameraTransform.rotate,cameraTransform.translate
	);
	Matrix4x4 viewMatrix = MatrixMath::Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MatrixMath::MakePerspectiveFovMatrix(
		0.45f, float(WinApp::kClientWidth) / float(WinApp::kClientHeight), 0.1f, 100.0f
	);
	Matrix4x4 worldViewProjectionMatrix = MatrixMath::Multiply(
		worldMatrix, MatrixMath::Multiply(viewMatrix, projectionMatrix));


	//////////////////////////////////////////////////////////
	//メインループ
	//////////////////////////////////////////////////////////
	
	//ウィンドウの×ボタンが押されるまでループ
	while (winApp->ProcessMessage() == 0) {
		
		//描画前処理
		directXCommon->PreDraw(texture->GetTextureSrvHandleGPU());

		transform.rotate.y += 0.03f;
		worldMatrix = MatrixMath::MakeAffineMatrix(transform.scale, transform.rotate, transform.translate);
		worldViewProjectionMatrix = MatrixMath::Multiply(
			worldMatrix, MatrixMath::Multiply(viewMatrix, projectionMatrix));

		directXCommon->SetWvpData(worldViewProjectionMatrix);

		

		//描画後処理
		directXCommon->PostDraw();
	}

	directXCommon->Finalize();
	winApp->Finalize();
	texture->Finalize();
	
	leakCheck.~D3DResourceLeakChecker();

	return 0;
}




