#pragma once
#include <enums.h>
#include <memory>
#include <string>
#include <types.h>


#include "RaycastResult.h"

namespace ModAPI
{
	class Ped;
	class Entity;

	class Camera
	{
	public:
		Camera(::Cam cameraHandle);

		static bool IsGameplayCameraRendering();
		static std::unique_ptr<Camera> GetRenderingCamera();
		static std::unique_ptr<Camera> Create(const std::string& name);
		static std::unique_ptr<Camera> Create(const std::string& name, const MMath::Vector3& position,
		                                                const MMath::Vector3& rotation, float fieldOfView);

		static void FadeOut(int durationMs);
		static void FadeIn(int durationMs);
		static bool IsFadingOut();
		static bool IsFadingIn();
		static bool IsFadedOut();
		static bool IsFadedIn();

		[[nodiscard]] bool IsRendering() const;
		[[nodiscard]] bool Exists() const;
		[[nodiscard]] bool IsActive() const;
		[[nodiscard]] ::Cam GetHandle() const;
		[[nodiscard]] MMath::Vector3 GetPosition() const;
		[[nodiscard]] MMath::Vector3 GetRotation() const;
		[[nodiscard]] MMath::Vector3 GetForwardPosition(float distance) const;
		[[nodiscard]] MMath::Vector3 GetForwardVector() const;
		[[nodiscard]] MMath::Vector3 GetForwardVector(float heading, float pitch) const;
		void SetActive(bool enable) const;
		void SetActiveWithInterp(const ModAPI::Camera& fromCamera, int durationMs, int easeLocation, int easeRotation) const;
		void SetFieldOfView(float newFOV) const;
		void SetRotation(const MMath::Vector3& newRotation, int rotationOrder) const;
		void SetPosition(const MMath::Vector3& newPosition) const;
		void AttachToEntity(const ModAPI::Entity* entity, const MMath::Vector3& offset, bool isRelative) const;
		void AttachToPedBone(const ModAPI::Ped& ped, int boneIndex, const MMath::Vector3& position, bool heading) const;
		void Detach() const;
		void PointAtPosition(const MMath::Vector3& position) const;
		void PointAtEntity(const ModAPI::Entity& entity, const MMath::Vector3& offset, bool isRelative) const;
		void StopPointing() const;
		void Destroy() const;
		[[nodiscard]] RaycastResult Raycast(float distance, eIntersectFlags flags) const;

	private:
		::Cam cameraHandle;
	};
}
