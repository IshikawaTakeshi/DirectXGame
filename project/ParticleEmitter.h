#pragma once
#include <string>
#include <wrl.h>

class SrvManager;
class Object3d;
class Object3dCommon;
class ParticleEmitter {
public:

	void Initialize(Object3dCommon* objectCommon,SrvManager* srvManager,const std::string& filePath);

	void Update();

	void Draw();


public: //getter

public: //setter

	void SetModel(const std::string& filePath);
	void SetCamera(Camera* camera) { camera_ = camera; }


private:

	static const uint32_t kNumInstance = 10;

	SrvManager* srvManager_ = nullptr;

	Object3dCommon* object3dCommon_ = nullptr;

	//モデル
	Model* model_ = nullptr;

	//TransformationMatrix用の頂点リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource_;
	//TransformationMatrix用の頂点データ
	TransformMatrix* transformMatrixData_ = nullptr;

	//平行光源用のリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> directionalLightResource_;
	DirectionalLightData* directionalLightData_ = nullptr;;

	//Transform
	Transform transforms_[kNumInstance];
	//WorldMatrix
	Matrix4x4 worldMatrix_;
	Matrix4x4 WVPMatrix_;
	//Camera
	Camera* camera_ = nullptr;
};

