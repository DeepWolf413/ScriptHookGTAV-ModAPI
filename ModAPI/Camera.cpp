#include "Camera.h"

#include <memory>
#include <shsdk/natives.h>


#include "Math.h"
#include "Ped.h"
#include "Player.h"

ModAPI::Camera::Camera(const CamHandle cameraHandle)
{ representedCamera = cameraHandle; }

std::unique_ptr<ModAPI::Camera> ModAPI::Camera::GetRenderingCamera()
{ return std::make_unique<Camera>(CAM::GET_RENDERING_CAM()); }

std::unique_ptr<ModAPI::Camera> ModAPI::Camera::Create(const std::string name)
{ return std::make_unique<Camera>(CAM::CREATE_CAM(name.c_str(), false)); }

std::unique_ptr<ModAPI::Camera> ModAPI::Camera::CreateWithParams(const std::string name, const Vector3& position, const Vector3& rotation, const float fieldOfView)
{ return std::make_unique<Camera>(CAM::CREATE_CAM_WITH_PARAMS(name.c_str(), position.x, position.y, position.z, rotation.x, rotation.y, rotation.z, fieldOfView, false, 2)); }

bool ModAPI::Camera::IsActive() const
{ return CAM::IS_CAM_ACTIVE(representedCamera); }

bool ModAPI::Camera::IsFadingOut()
{ return CAM::IS_SCREEN_FADING_OUT(); }

bool ModAPI::Camera::IsFadingIn()
{ return CAM::IS_SCREEN_FADING_IN(); }

bool ModAPI::Camera::IsFadedOut()
{ return CAM::IS_SCREEN_FADED_OUT(); }

bool ModAPI::Camera::IsFadedIn()
{ return CAM::IS_SCREEN_FADED_IN(); }

bool ModAPI::Camera::IsRendering() const
{ return CAM::IS_CAM_RENDERING(representedCamera); }

bool ModAPI::Camera::Exists() const
{ return representedCamera == NULL || CAM::DOES_CAM_EXIST(representedCamera); }

CamHandle ModAPI::Camera::GetHandle() const
{ return representedCamera; }

Vector3 ModAPI::Camera::GetPosition() const
{
	const bool useGameplayCamera = !CAM::DOES_CAM_EXIST(representedCamera) || !CAM::IS_CAM_RENDERING(representedCamera);
	return useGameplayCamera ? CAM::GET_GAMEPLAY_CAM_COORD() : CAM::GET_CAM_COORD(representedCamera);
}

Vector3 ModAPI::Camera::GetRotation() const
{
	const bool useGameplayCamera = !CAM::DOES_CAM_EXIST(representedCamera) || !CAM::IS_CAM_RENDERING(representedCamera);
	return useGameplayCamera ? CAM::GET_GAMEPLAY_CAM_ROT(2) : CAM::GET_CAM_ROT(representedCamera, 2);
}

Vector3 ModAPI::Camera::GetForwardPosition(const float distance) const
{
	const Vector3 position = GetPosition();
	const Vector3 forwardVector = GetForwardVector() * distance;
	return position + forwardVector;
}

Vector3 ModAPI::Camera::GetForwardVector() const
{
	const Vector3 rotation = GetRotation();
	const float x = MathUtils::ToRadian(rotation.x);
	const float z = MathUtils::ToRadian(rotation.z);
	return GetForwardVector(z, x);
}

Vector3 ModAPI::Camera::GetForwardVector(const float heading, const float pitch) const
{
	const float num = abs(cos(pitch));
	Vector3 dir;
	dir.x = (-sin(heading) * num);
	dir.y = (cos(heading) * num);
	dir.z = (sin(pitch));
	return dir;
}

void ModAPI::Camera::SetActive(const bool enable) const
{ CAM::SET_CAM_ACTIVE(representedCamera, enable); }

void ModAPI::Camera::SetActiveWithInterp(const Camera* fromCamera, const int durationMs, const int easeLocation, const int easeRotation) const
{ CAM::SET_CAM_ACTIVE_WITH_INTERP(representedCamera, fromCamera->GetHandle(), durationMs, easeLocation, easeRotation); }

void ModAPI::Camera::SetFieldOfView(const float newFOV) const
{ CAM::SET_CAM_FOV(representedCamera, newFOV); }

void ModAPI::Camera::SetRotation(const Vector3& newRotation, const int rotationOrder) const
{ CAM::SET_CAM_ROT(representedCamera, newRotation.x, newRotation.y, newRotation.z, rotationOrder); }

void ModAPI::Camera::SetPosition(const Vector3& newPosition) const
{ CAM::SET_CAM_COORD(representedCamera, newPosition.x, newPosition.y, newPosition.z); }

void ModAPI::Camera::AttachToEntity(const Entity* entity, const Vector3& offset, const bool isRelative) const
{ CAM::ATTACH_CAM_TO_ENTITY(representedCamera, entity->GetHandle(), offset.x, offset.y, offset.z, isRelative); }

void ModAPI::Camera::AttachToPedBone(const PedHandle ped, const int boneIndex, const Vector3& position, const bool heading) const
{ CAM::ATTACH_CAM_TO_PED_BONE(representedCamera, ped, boneIndex, position.x, position.y, position.z, heading); }

void ModAPI::Camera::Detach() const
{
	CAM::DETACH_CAM(representedCamera);
	AttachToEntity(nullptr, Vector3(), false);
}

void ModAPI::Camera::PointAtPosition(const Vector3 position) const
{ CAM::POINT_CAM_AT_COORD(representedCamera, position.x, position.y, position.z); }

void ModAPI::Camera::PointAtEntity(const Entity* entity, const Vector3& offset, const bool isRelative) const
{ CAM::POINT_CAM_AT_ENTITY(representedCamera, entity->GetHandle(), offset.x, offset.y, offset.z, isRelative); }

void ModAPI::Camera::StopPointing() const
{ CAM::STOP_CAM_POINTING(representedCamera); }

void ModAPI::Camera::FadeOut(const int durationMs)
{ CAM::DO_SCREEN_FADE_OUT(durationMs); }

void ModAPI::Camera::FadeIn(const int durationMs)
{ CAM::DO_SCREEN_FADE_IN(durationMs); }

void ModAPI::Camera::Destroy() const
{ CAM::DESTROY_CAM(representedCamera, false); }

RaycastResult ModAPI::Camera::Raycast(const float distance, const eTraceFlags flags) const
{
	const auto camPos = GetPosition();
	const auto camForwardPos = GetForwardPosition(distance);
	const auto playerPed = Player::GetPed();
	const int shapeTestHandle = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(camPos.x, camPos.y, camPos.z, camForwardPos.x, camForwardPos.y, camForwardPos.z, static_cast<int>(flags), playerPed->GetHandle(), 7);
	return RaycastResult(shapeTestHandle);
}
