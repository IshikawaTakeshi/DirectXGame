#include "Camera.h"
#include "MatrixMath.h"
#include "WinApp.h"
#include "ImGuiManager.h"

Camera::Camera()
	: transform_({ {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} })
	, fovX_(0.45f)
	, aspectRatio_(float(WinApp::kClientWidth) / float(WinApp::kClientHeight))
	, nearClip_(0.1f)
	, farClip_(100.0f)
	, worldMatrix_(MatrixMath::MakeAffineMatrix(transform_.scale, transform_.rotate, transform_.translate))
	, viewMatrix_(MatrixMath::Inverse(worldMatrix_))
	, projectionMatrix_(MatrixMath::MakePerspectiveFovMatrix(fovX_, aspectRatio_, nearClip_, farClip_))
	, viewProjectionMatrix_(MatrixMath::Multiply(viewMatrix_, projectionMatrix_)) 
{}

Camera::~Camera() {}

void Camera::Update() {
	worldMatrix_ = MatrixMath::MakeAffineMatrix(
		transform_.scale,
		transform_.rotate,
		transform_.translate
	);

	viewMatrix_ = MatrixMath::Inverse(worldMatrix_);

	projectionMatrix_ = MatrixMath::MakePerspectiveFovMatrix(
		fovX_,
		aspectRatio_,
		nearClip_,
		farClip_
	);

	viewProjectionMatrix_ = MatrixMath::Multiply(viewMatrix_, projectionMatrix_);
}

#ifdef _DEBUG
void Camera::UpdateImGui() {
	ImGui::DragFloat3("Translate", &transform_.translate.x, 0.01f);
	ImGui::DragFloat3("Rotate", &transform_.rotate.x, 0.01f);
	ImGui::DragFloat("FovX", &fovX_, 0.01f);
}
#endif // DEBUG

