#pragma once
#include <memory>
#include <string>
#include <shsdk/enums.h>
#include <shsdk/types.h>


#include "RaycastResult.h"
#include "math/Vector3.h"

namespace ModAPI
{
	class Entity;

	class Camera
	{
	public:
		Camera(CamHandle cameraHandle);

		static bool IsGameplayCameraRendering();
		static std::unique_ptr<Camera> GetRenderingCamera();
		static std::unique_ptr<Camera> Create(const std::string& name);
		static std::unique_ptr<Camera> CreateWithParams(const std::string& name, const Vector3& position,
		                                                const Vector3& rotation, float fieldOfView);

		static void FadeOut(int durationMs);
		static void FadeIn(int durationMs);
		static bool IsFadingOut();
		static bool IsFadingIn();
		static bool IsFadedOut();
		static bool IsFadedIn();

		[[nodiscard]] bool IsRendering() const;
		[[nodiscard]] bool Exists() const;
		[[nodiscard]] bool IsActive() const;
		[[nodiscard]] CamHandle GetHandle() const;
		[[nodiscard]] Vector3 GetPosition() const;
		[[nodiscard]] Vector3 GetRotation() const;
		[[nodiscard]] Vector3 GetForwardPosition(float distance) const;
		[[nodiscard]] Vector3 GetForwardVector() const;
		[[nodiscard]] Vector3 GetForwardVector(float heading, float pitch) const;
		void SetActive(bool enable) const;
		void SetActiveWithInterp(const Camera& fromCamera, int durationMs, int easeLocation, int easeRotation) const;
		void SetFieldOfView(float newFOV) const;
		void SetRotation(const Vector3& newRotation, int rotationOrder) const;
		void SetPosition(const Vector3& newPosition) const;
		void AttachToEntity(const Entity* entity, const Vector3& offset, bool isRelative) const;
		void AttachToPedBone(PedHandle ped, int boneIndex, const Vector3& position, bool heading) const;
		void Detach() const;
		void PointAtPosition(Vector3 position) const;
		void PointAtEntity(const Entity& entity, const Vector3& offset, bool isRelative) const;
		void StopPointing() const;
		void Destroy() const;
		[[nodiscard]] RaycastResult Raycast(float distance, eTraceFlags flags) const;

	private:
		CamHandle representedCamera;
	};
}
