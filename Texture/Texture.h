#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>

#include <dxcapi.h>

#include <wrl.h>
#include <cassert>
#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include "../externals/DirectXTex/DirectXTex.h"
#include "../externals/DirectXTex/d3dx12.h"


class DirectXCommon;
class Texture {
public:

	/////////////////////////////////////////////////////////////////////////////////////
	///			publicメンバ関数
	/////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Texture() = default;

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Texture();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(uint32_t index, DirectXCommon* dxCommon, const std::string& filePath);

	/// <summary>
	/// 終了・開放処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// テクスチャデータの読み込み関数
	/// </summary>
	/// <param name="filePath">画像のファイルパス</param>
	/// <returns>ミップマップ付きのデータ</returns>
	DirectX::ScratchImage LoadTexture(const std::string& filePath);

	/// <summary>
	/// TextureResourceの作成関数
	/// </summary>
	/// <param name="device"></param>
	/// <param name="metadata"></param>
	/// <returns>生成されたリソース</returns>
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(
	const Microsoft::WRL::ComPtr<ID3D12Device>& device, const DirectX::TexMetadata& metadata);

	/// <summary>
	/// TextureResourceにデータを転送する関数
	/// </summary>
	/// <param name="texture"></param>
	/// <param name="mipImages"></param>
	void UploadTextureData(
		Microsoft::WRL::ComPtr<ID3D12Resource> texture, const DirectX::ScratchImage& mipImages);
	
	/// <summary>
	/// DepthStencilResourceの作成関数
	/// </summary>
	/// <param name="device"></param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <returns>DepthStencilResource</returns>
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateDepthStencilTextureResource(
		const Microsoft::WRL::ComPtr<ID3D12Device>& device, int32_t width, int32_t height);

public:

	/////////////////////////////////////////////////////////////////////////////////////
	///			getter
	/////////////////////////////////////////////////////////////////////////////////////

	/// <summary>
	/// textureSrvHandleGPUの取得
	/// </summary>
	D3D12_GPU_DESCRIPTOR_HANDLE GetTextureSrvHandleGPU() const { return textureSrvHandleGPU_; }

	
	

private:

	/////////////////////////////////////////////////////////////////////////////////////
	///			privateメンバ変数
	/////////////////////////////////////////////////////////////////////////////////////

	std::string filePath_;

	D3D12_CPU_DESCRIPTOR_HANDLE textureSrvHandleCPU_ = {};
	D3D12_GPU_DESCRIPTOR_HANDLE textureSrvHandleGPU_ = {};
	
	Microsoft::WRL::ComPtr<ID3D12Resource> textureResource_ = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> depthStencilResource_ = nullptr;


};

