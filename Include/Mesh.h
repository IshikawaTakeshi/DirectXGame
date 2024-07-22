#pragma once
#include "../Include/ResourceDataStructure.h"
#include <d3d12.h>
#include <wrl.h>

class Material;
class Mesh {
public:

	Mesh() = default;
	~Mesh() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void InitializeMesh();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	//================================= VertexBufferResource ==================================//

	/// <summary>
	/// 球体の頂点バッファリソース初期化
	/// </summary>
	void InitializeVertexResourceSphere(Microsoft::WRL::ComPtr<ID3D12Device> device);

	/// <summary>
	/// スプライトの頂点バッファリソース初期化
	/// </summary>
	void InitializeVertexResourceSprite(Microsoft::WRL::ComPtr<ID3D12Device> device);

	/// <summary>
	/// 三角形の頂点バッファリソース初期化
	/// </summary>
	void InitializeVertexResourceTriangle(Microsoft::WRL::ComPtr<ID3D12Device> device);

	/// <summary>
	/// 頂点バッファビューの取得
	/// </summary>
	const D3D12_VERTEX_BUFFER_VIEW GetVertexBufferView() { return vertexBufferView_; }


	//================================= IndexBufferResource ==================================//

	/// <summary>
	/// 球体のIndexResource初期化
	/// </summary>
	void InitializeIndexResourceSphere(Microsoft::WRL::ComPtr<ID3D12Device> device);

	/// <summary>
	/// スプライトのIndexResource初期化
	/// </summary>
	void InitializeIndexResourceSprite(Microsoft::WRL::ComPtr<ID3D12Device> device);

	/// <summary>
	/// インデックスバッファビューの取得
	/// </summary>
	const D3D12_INDEX_BUFFER_VIEW GetIndexBufferView() { return indexBufferView_; }

	//================================= MaterialBufferResource ==================================//

	Material* GetMaterial() { return material_; }

public:

	//球体の分割数
	static inline const uint32_t kSubdivision = 16;

private:

	
	//頂点バッファリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_{};

	//IndexBufferView用のリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> indexResource_;
	D3D12_INDEX_BUFFER_VIEW indexBufferView_{};

	//マテリアル
	Material* material_ = nullptr;

};

