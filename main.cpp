#pragma warning(push)
//C4023の警告を見なかったことにする
#pragma warning(disable:4023)
//Include
#include "Include/WinApp.h"
#include "Include/Logger.h"
#include "Include/DirectXCommon.h"
#include "Include/Input.h"
#include "Audio/Audio.h"

#include "MyMath/Transform.h"
#include "MyMath/MatrixMath.h"
#include "Texture/Texture.h"
#include "Sprite/Sprite.h"
#include "Triangle/Triangle.h"
#include "Sphere/Sphere.h"
#include "ModelData/Model.h"
#include <dxgidebug.h>
#pragma comment(lib,"dxguid.lib")

#pragma region imgui
#ifdef _DEBUG
#include "externals/imgui/imgui.h"
#include "externals/imgui/imgui_impl_dx12.h"
#include "externals/imgui/imgui_impl_win32.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif // DEBUG
#pragma endregion

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


	D3DResourceLeakChecker leakCheck;

	//タイトルバーの名前の入力
	WinApp* winApp = WinApp::GetInstance();
	winApp->Initialize(L"CG2_06_02");

	//DirectX初期化
	DirectXCommon* directXCommon = new DirectXCommon();
	directXCommon->Initialize(winApp);

#pragma region ImGui初期化
#ifdef _DEBUG
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(winApp->GetHwnd());
	ImGui_ImplDX12_Init(directXCommon->GetDevice(),
		directXCommon->GetBufferCount(),
		directXCommon->GetRtvFormat(),
		directXCommon->GetSrvHeap(),
		directXCommon->GetSrvHeap()->GetCPUDescriptorHandleForHeapStart(),
		directXCommon->GetSrvHeap()->GetGPUDescriptorHandleForHeapStart()
	);
#endif // DEBUG
#pragma endregion

	//入力初期化
	Input* input = Input::GetInstance();
	input->Initialize(winApp);
	//オーディオ
	Audio* audio = Audio::GetInstance();
	audio->Initialize();
	
	//サウンドデータ
	Audio::SoundData soundData1;
	soundData1 = audio->SoundLoadWave("Resources/Alarm01.wav");


	//テクスチャ初期化
	Texture* texture1 = new Texture();
	texture1->Initialize(1, directXCommon, "./Resources/uvChecker.png");
	//テクスチャ2初期化
	Texture* texture2 = new Texture();
	texture2->Initialize(2, directXCommon, "./Resources/monsterBall.png");

	//カメラ
	Transform cameraTransform{ {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,-10.0f} };
	Matrix4x4 cameraMatrix = MatrixMath::MakeAffineMatrix(
		cameraTransform.scale,
		cameraTransform.rotate,
		cameraTransform.translate
	);

	//モデル
	Model* model1 = new Model();
	model1->Initialize(directXCommon, cameraMatrix, "Resources", "obj_mtl_blend", "axis.obj");
	
	Model* model2 = new Model();
	model2->Initialize(directXCommon, cameraMatrix, "Resources", "obj_mtl_blend", "plane.obj");

	Model* model3 = new Model();
	model3->Initialize(directXCommon, cameraMatrix, "Resources", "obj_mtl_blend", "bunny.obj");

	Model* model4 = new Model();
	model4->Initialize(directXCommon, cameraMatrix, "Resources", "obj_mtl_blend", "teapot.obj");

	//球
	Sphere* sphere = new Sphere();
	sphere->Initialize(directXCommon, cameraMatrix, true, "./Resources/uvChecker.png");

	//スプライト
	Sprite* sprite = new Sprite();
	sprite->Initialize(directXCommon,true, "./Resources/uvChecker.png");

	//モデル描画のフラグ
	bool drawModelSwitch1 = false;
	bool drawModelSwitch2 = false;
	bool drawModelSwitch3 = false;
	bool drawModelSwitch4 = false;
	bool isDrawSphere = true;
	bool isDrawSprite = true;

	/////////////////////////////////////////////////////////////////////////////////////////////
	//										メインループ
	/////////////////////////////////////////////////////////////////////////////////////////////

	//ウィンドウの×ボタンが押されるまでループ

	while (true) {
		//メッセージ処理
		if (winApp->ProcessMessage()) {
			//ウィンドウの×ボタンが押されたらループを抜ける
			break;
		}


		//========================== 更新処理　==========================//


#ifdef _DEBUG
		//ImGui受付開始
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		//開発用UIの処理。実際に開発用のUIを出す場合はここをゲーム特有の処理に置き換える
		ImGui::ShowDemoWindow();
#endif // DEBUG

		//入力更新
		input->Update();

		//オーディオ再生
		if (input->TriggerKey(DIK_A)) {
			audio->SoundPlayWave(audio->GetXAudio2(), soundData1);
		}

		//モデルの更新処理
		model1->Update();
		model2->Update();
		
		model3->Update();
		model4->Update();

		//球
		sphere->Update();


		//スプライト
		sprite->Update();

		ImGui::Begin("DrawSwitch");
		ImGui::Checkbox("Model:axis", &drawModelSwitch1);
		ImGui::Checkbox("Model:plane", &drawModelSwitch2);
		ImGui::Checkbox("Model:bunny", &drawModelSwitch3);
		ImGui::Checkbox("Model:teapot", &drawModelSwitch4);
		ImGui::Checkbox("Sphere", &isDrawSphere);
		ImGui::Checkbox("Sprite", &isDrawSprite);
		ImGui::Text("Akey : SoundPlay");
		ImGui::End();


		//========================== 描画処理　==========================//

		//描画前処理
		directXCommon->PreDraw();


		if (input->TriggerKey(DIK_SPACE)) {
			//モデルのテクスチャを変更
			sphere->SetTexture(texture2);
		}
		if (input->PushKey(DIK_B)) {
			//モデルのテクスチャを変更
			sphere->SetTexture(texture1);
		}

		if (drawModelSwitch1 == true) {
			model1->DrawCall(directXCommon);
		}
		if (drawModelSwitch2 == true) {
			model2->DrawCall(directXCommon);
		}
		if (drawModelSwitch3 == true) {
			model3->DrawCall(directXCommon);
		}
		if (drawModelSwitch4 == true) {
			model4->DrawCall(directXCommon);
		}

		if (isDrawSphere == true) {
			sphere->DrawCall(directXCommon);
		}
		if (isDrawSprite == true) {
			sprite->DrawCall(directXCommon);
		}

		//描画後処理
		directXCommon->PostDraw();
	}


	/*==========ImGuiの開放==========*/
#ifdef _DEBUG
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
#endif // DEBUG

	audio->Finalize(soundData1);
	directXCommon->Finalize();
	winApp->Finalize();
	
	delete model4;
	delete model3;
	delete model2;
	delete model1;
	delete sphere;
	delete texture1;
	delete texture2;
	delete sprite;



	leakCheck.~D3DResourceLeakChecker();

	return 0;
}



