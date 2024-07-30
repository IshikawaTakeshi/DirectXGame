#pragma once
#include "../Vector3.h"
#include "../MyMath/Matrix4x4.h"
#include "../MyMath/TransformMatrix.h"
#include "../MyMath/Transform.h"
#include "../Include/ResourceDataStructure.h"
#include "../Include/Mesh.h"
#include <stdint.h>
#include <string>
#include <vector>
#include <d3d12.h>
#include <wrl.h>

class DirectXCommon;
class Sphere {
public:
	Sphere() = default;
	~Sphere();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Matrix4x4 cameraView, uint32_t enableLight, const std::string& textureFilePath);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	void UpdateImGui();

	bool ImGuiComboUI();

	/// <summary>
	/// directionalLightData初期化
	/// </summary>
	void InitializeDirectionalLightData(DirectXCommon* dxCommon);

	/// <summary>
	/// 描画処理
	/// </summary>
	void DrawCall(DirectXCommon* dxCommon);

public: //ゲッター

public: //セッター

	void SetTexture(Texture* texture) {
		mesh_->SetTexture(texture);
	}


private:

	//メッシュ
	Mesh* mesh_;

	//TransformationMatrix用の頂点リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource_;
	//TransformationMatrix用の頂点データ
	TransformMatrix* transformMatrixData_ = nullptr;

	//平行光源用のリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> directionalLightResource_;
	DirectionalLightData* directionalLightData_ = nullptr;;

	//CPU用のTransform
	Transform transform_{};
	//行列
	Matrix4x4 worldMatrix_;
	Matrix4x4 viewMatrix_;
	Matrix4x4 projectionMatrix_;
	Matrix4x4 worldViewProjectionMatrix_;

	//Texture
	bool useMonsterBall = true;

};

