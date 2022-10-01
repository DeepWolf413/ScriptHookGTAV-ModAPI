#pragma once
#include <string>

#include <types.h>

namespace ModAPI
{
	namespace MMath
	{
		struct Vector3;
	}

	class Model {
	public:
		Model(const std::string& name);
		Model(Hash hash);

		[[nodiscard]] Hash GetHash() const;
		[[nodiscard]] bool IsValid() const;
		[[nodiscard]] bool IsInCdImage() const;
		[[nodiscard]] bool IsLoaded() const;
		[[nodiscard]] bool IsCollisionLoaded() const;
		[[nodiscard]] bool IsBoat() const;
		[[nodiscard]] bool IsPed() const;
		[[nodiscard]] bool IsTrain() const;
		[[nodiscard]] bool IsVehicle() const;
		[[nodiscard]] bool IsHelicopter() const;
		[[nodiscard]] bool IsJetski() const;
		[[nodiscard]] bool IsPlane() const;
		[[nodiscard]] bool IsCar() const;
		[[nodiscard]] bool IsBike() const;
		[[nodiscard]] bool IsBicycle() const;
		[[nodiscard]] bool IsQuadBike() const;
		
		void GetDimensions(MMath::Vector3& minimum, MMath::Vector3& maximum) const;
		[[nodiscard]] MMath::Vector3 GetDimensions() const;

		[[nodiscard]] bool Request() const;
		[[nodiscard]] bool Request(int timeoutMs) const;

		void MarkAsNoLongerNeeded() const;

	private:
		Hash hash {0x0};
	};
}
