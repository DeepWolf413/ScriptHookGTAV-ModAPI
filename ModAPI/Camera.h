#pragma once
#include <memory>
#include <string>
#include <inc/enums.h>
#include <inc/types.h>


#include "RaycastResult.h"
#include "math/Vector3.h"

namespace ModAPI
{
	class Entity;

	class Camera {
	public:
		Camera(CamHandle cameraHandle);
		
		static std::unique_ptr<Camera> GetRenderingCamera();
		static std::unique_ptr<Camera> Create(std::string name);
		static std::unique_ptr<Camera> CreateWithParams(std::string name, Vector3 position, Vector3 rotation, float fieldOfView);
		
		static void   FadeOut(int durationMs);
		static void   FadeIn(int durationMs);
		static bool   IsFadingOut();
		static bool   IsFadingIn();
		static bool   IsFadedOut();
		static bool   IsFadedIn();

		bool		  IsRendering() const;
		bool		  Exists() const;
		bool          IsActive() const;
		CamHandle           GetHandle() const;
		Vector3       GetPosition() const;
		Vector3       GetRotation() const;
		Vector3       GetForwardPosition(float distance) const;
		Vector3       GetForwardVector() const;
		Vector3       GetForwardVector(float heading, float pitch) const;
		void          SetActive(bool enable) const;
		void          SetActiveWithInterp(Camera* fromCamera, int durationMs, int easeLocation, int easeRotation) const;
		void          SetFieldOfView(float newFOV) const;
		void          SetRotation(Vector3 newRotation, int rotationOrder) const;
		void          SetPosition(Vector3 newPosition) const;
		void          AttachToEntity(Entity* entity, Vector3 offset, bool isRelative) const;
		void          AttachToPedBone(::PedHandle ped, int boneIndex, Vector3 position, bool heading) const;
		void          Detach() const;
		void          PointAtPosition(Vector3 position) const;
		void          PointAtEntity(Entity* entity, Vector3 offset, bool isRelative) const;
		void          StopPointing() const;
		void          Destroy() const;
		RaycastResult Raycast(float distance, eTraceFlags flags) const;

	private:
		CamHandle representedCamera;
	};
}
