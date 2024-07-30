#pragma once
#include "../Include/ResourceDataStructure.h"
#include "../MyMath/Transform.h"
#include "../Texture/Texture.h"
#include <d3d12.h>
#include <wrl.h>
#include <string>
#include <cstdint>


class DirectXCommon;
class Material {
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	///			public関数
	////////////////////////////////////////////////////////////////////////////////////////////////////

	Material() = default;
	~Material();

	/// <summary>
	/// 初期化
	/// </summary>
	void InitializeTexture(uint32_t index, DirectXCommon* dxCommon, uint32_t enableLight, const std::string& filePath);

	/// <summary>
	/// ImGuiによる更新処理
	/// </summary>
	void UpdateImGui();

	/// <summary>
	/// マテリアルリソース初期化
	/// </summary>
	void InitializeMaterialResource(Microsoft::WRL::ComPtr<ID3D12Device> device, uint32_t enableLight);

public: 

	////////////////////////////////////////////////////////////////////////////////////////////////////
	///			getter
	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// マテリアルリソースの取得
	/// </summary>
	ID3D12Resource* GetMaterialResource() { return materialResource_.Get(); }

	/// <summary>
	/// テクスチャの取得
	/// </summary>
	/// <returns></returns>
	Texture* GetTexture() { return texture_; }

public: 
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	///			setter
	////////////////////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	///uvTransformの設定
	/// </summary>
	void SetUvTransform(const Transform& uvTransform) { uvTransform_ = uvTransform; }

	/// <summary>
	/// マテリアルデータの設定
	/// </summary>
	void SetMaterialData(MaterialData* materialData) { materialData_ = materialData; }

	/// <summary>
	/// テクスチャの設定
	/// </summary>
	void SetTexture(Texture* texture) { texture_ = texture; }

	void SetEnableLight(uint32_t enableLight) { materialData_->enableLighting = enableLight; }


private:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	///			privateメンバ変数
	////////////////////////////////////////////////////////////////////////////////////////////////////

	//テクスチャ
	Texture* texture_;

	//マテリアルリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_;
	MaterialData* materialData_ = nullptr;

	//uvTransform
	Transform uvTransform_;

};

