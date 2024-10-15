#include "ParticleEmitter.h"
#include "SrvManager.h"
#include "Object3d.h"
#include "Object3dCommon.h"
#include "Model.h"
#include "ModelManager.h"
#include "ModelCommon.h"
#include "DirectXCommon.h"
#include "Mesh.h"
#include "ModelManager.h"
#include "MatrixMath.h"

void ParticleEmitter::Initialize(Object3dCommon* objectCommon,SrvManager* srvManager, const std::string& filePath) {
	object3dCommon_ = objectCommon;
	SetModel(filePath);
	model_->GetMesh()->GetMaterial()->SetEnableLighting(true);
	//スプライト用のTransformationMatrix用のVertexResource生成
	wvpResource_ = DirectXCommon::CreateBufferResource(object3dCommon_->GetDirectXCommon()->GetDevice(), sizeof(TransformMatrix));

	//TransformationMatrix用
	wvpResource_->Map(0, nullptr, reinterpret_cast<void**>(&transformMatrixData_));

	//単位行列を書き込んでおく
	transformMatrixData_->WVP = MatrixMath::MakeIdentity4x4();

	//平行光源用Resourceの作成
	directionalLightResource_ = DirectXCommon::CreateBufferResource(object3dCommon_->GetDirectXCommon()->GetDevice(), sizeof(DirectionalLightData));
	directionalLightData_ = nullptr;
	//データを書き込むためのアドレスを取得
	directionalLightResource_->Map(0, nullptr, reinterpret_cast<void**>(&directionalLightData_));
	//光源の色を書き込む
	directionalLightData_->color_ = { 1.0f,1.0f,1.0f,1.0f };
	//光源の方向を書き込む
	directionalLightData_->direction_ = { 0.0f,-1.0f,0.0f };
	//光源の輝度書き込む
	directionalLightData_->intensity_ = 1.0f;
	//CPUで動かす用のTransform
	for (uint32_t index = 0; index < kNumInstance; index++) {
		transforms_[index].scale = { 1.0f,1.0f,1.0f };
		transforms_[index].rotate = { 0.0f,0.0f,0.0f };
		transforms_[index].translate = { index * 0.1f,index * 0.1f, index * 0.1f };
	}

	//アフィン行列
	worldMatrix_ = MatrixMath::MakeIdentity4x4();
	//カメラのセット
	camera_ = object3dCommon_->GetDefaultCamera();
	srvManager_ = srvManager;
}

void ParticleEmitter::Update() {

}

void ParticleEmitter::SetModel(const std::string& filePath) {
	model_ = ModelManager::GetInstance()->FindModel(filePath);
}
