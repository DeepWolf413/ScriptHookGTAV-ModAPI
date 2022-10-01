#include "Camera.h"

#include <memory>
#include <natives.h>

#include "Math.h"
#include "Ped.h"
#include "Player.h"

namespace ModAPI
{
	Camera::Camera(const ::Cam cameraHandle)
	{ this->cameraHandle = cameraHandle; }

	bool Camera::IsGameplayCameraRendering()
	{ return CAM::IS_GAMEPLAY_CAM_RENDERING(); }

	std::unique_ptr<ModAPI::Camera> Camera::GetRenderingCamera()
	{ return std::make_unique<Camera>(CAM::GET_RENDERING_CAM()); }

	std::unique_ptr<ModAPI::Camera> Camera::Create(const std::string& name)
	{ return std::make_unique<Camera>(CAM::CREATE_CAM(name.c_str(), false)); }

	std::unique_ptr<ModAPI::Camera> Camera::Create(const std::string& name, const MMath::Vector3& position, const MMath::Vector3& rotation, const float fieldOfView)
	{ return std::make_unique<Camera>(CAM::CREATE_CAM_WITH_PARAMS(name.c_str(), position.X, position.Y, position.Z, rotation.X, rotation.Y, rotation.Z, fieldOfView, false, 2)); }

	bool Camera::IsActive() const
	{ return CAM::IS_CAM_ACTIVE(cameraHandle); }

	bool Camera::IsFadingOut()
	{ return CAM::IS_SCREEN_FADING_OUT(); }

	bool Camera::IsFadingIn()
	{ return CAM::IS_SCREEN_FADING_IN(); }

	bool Camera::IsFadedOut()
	{ return CAM::IS_SCREEN_FADED_OUT(); }

	bool Camera::IsFadedIn()
	{ return CAM::IS_SCREEN_FADED_IN(); }

	bool Camera::IsRendering() const
	{ return CAM::IS_CAM_RENDERING(cameraHandle); }

	bool Camera::Exists() const
	{ return cameraHandle == NULL || CAM::DOES_CAM_EXIST(cameraHandle); }

	::Cam Camera::GetHandle() const
	{ return cameraHandle; }

	MMath::Vector3 Camera::GetPosition() const
	{
		const bool useGameplayCamera = !CAM::DOES_CAM_EXIST(cameraHandle) || !CAM::IS_CAM_RENDERING(cameraHandle);
		return MMath::Vector3::FromSHVector3(useGameplayCamera ? CAM::GET_GAMEPLAY_CAM_COORD() : CAM::GET_CAM_COORD(cameraHandle));
	}

	MMath::Vector3 Camera::GetRotation() const
	{
		const bool useGameplayCamera = !CAM::DOES_CAM_EXIST(cameraHandle) || !CAM::IS_CAM_RENDERING(cameraHandle);
		return MMath::Vector3::FromSHVector3(useGameplayCamera ? CAM::GET_GAMEPLAY_CAM_ROT(2) : CAM::GET_CAM_ROT(cameraHandle, 2));
	}

	MMath::Vector3 Camera::GetForwardPosition(const float distance) const
	{
		const auto position = GetPosition();
		const auto forwardVector = GetForwardVector() * distance;
		return position + forwardVector;
	}

	MMath::Vector3 Camera::GetForwardVector() const
	{
		const auto rotation = GetRotation();
		const float x = MathHelpers::ToRadian(rotation.X);
		const float z = MathHelpers::ToRadian(rotation.Z);
		return GetForwardVector(z, x);
	}

	MMath::Vector3 Camera::GetForwardVector(const float heading, const float pitch) const
	{
		const float num = abs(cos(pitch));
		MMath::Vector3 dir;
		dir.X = (-sin(heading) * num);
		dir.Y = (cos(heading) * num);
		dir.Z = (sin(pitch));
		return dir;
	}

	void Camera::SetActive(const bool enable) const
	{ CAM::SET_CAM_ACTIVE(cameraHandle, enable); }

	void Camera::SetActiveWithInterp(const Camera& fromCamera, const int durationMs, const int easeLocation, const int easeRotation) const
	{ CAM::SET_CAM_ACTIVE_WITH_INTERP(cameraHandle, fromCamera.GetHandle(), durationMs, easeLocation, easeRotation); }

	void Camera::SetFieldOfView(const float newFOV) const
	{ CAM::SET_CAM_FOV(cameraHandle, newFOV); }

	void Camera::SetRotation(const MMath::Vector3& newRotation, const int rotationOrder) const
	{ CAM::SET_CAM_ROT(cameraHandle, newRotation.X, newRotation.Y, newRotation.Z, rotationOrder); }

	void Camera::SetPosition(const MMath::Vector3& newPosition) const
	{ CAM::SET_CAM_COORD(cameraHandle, newPosition.X, newPosition.Y, newPosition.Z); }

	void Camera::AttachToEntity(const ModAPI::Entity* entity, const MMath::Vector3& offset, const bool isRelative) const
	{ CAM::ATTACH_CAM_TO_ENTITY(cameraHandle, entity->GetHandle(), offset.X, offset.Y, offset.Z, isRelative); }

	void Camera::AttachToPedBone(const ModAPI::Ped& ped, const int boneIndex, const MMath::Vector3& position, const bool heading) const
	{ CAM::ATTACH_CAM_TO_PED_BONE(cameraHandle, ped.GetHandle(), boneIndex, position.X, position.Y, position.Z, heading); }

	void Camera::Detach() const
	{
		CAM::DETACH_CAM(cameraHandle);
		AttachToEntity(nullptr, {}, false);
	}

	void Camera::PointAtPosition(const MMath::Vector3& position) const
	{ CAM::POINT_CAM_AT_COORD(cameraHandle, position.X, position.Y, position.Z); }

	void Camera::PointAtEntity(const ModAPI::Entity& entity, const MMath::Vector3& offset, const bool isRelative) const
	{ CAM::POINT_CAM_AT_ENTITY(cameraHandle, entity.GetHandle(), offset.X, offset.Y, offset.Z, isRelative); }

	void Camera::StopPointing() const
	{ CAM::STOP_CAM_POINTING(cameraHandle); }

	void Camera::FadeOut(const int durationMs)
	{ CAM::DO_SCREEN_FADE_OUT(durationMs); }

	void Camera::FadeIn(const int durationMs)
	{ CAM::DO_SCREEN_FADE_IN(durationMs); }

	void Camera::Destroy() const
	{ CAM::DESTROY_CAM(cameraHandle, false); }

	RaycastResult Camera::Raycast(const float distance, const eIntersectFlags flags) const
	{
		const auto camPos = GetPosition();
		const auto camForwardPos = GetForwardPosition(distance);
		const auto playerPed = Player::GetPed();
		const int shapeTestHandle = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(camPos.X, camPos.Y, camPos.Z, camForwardPos.X, camForwardPos.Y, camForwardPos.Z, static_cast<int>(flags), playerPed.GetHandle(), 7);
		return {shapeTestHandle};
	}
}