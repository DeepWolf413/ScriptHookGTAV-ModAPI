#pragma once
#include <string>

#include <inc/types.h>

struct Vector3;

namespace ModAPI
{
	class Model {
	public:
		Model(std::string name);
		Model(Hash hash);

		Hash GetHash() const;
		bool IsValid() const;
		bool IsInCdImage() const;
		bool IsLoaded() const;
		bool IsCollisionLoaded() const;
		bool IsBoat() const;
		bool IsPed() const;
		bool IsTrain() const;
		bool IsVehicle() const;

		void    GetDimensions(Vector3* minimum, Vector3* maximum) const;
		Vector3 GetDimensions() const;

		bool Request() const;
		bool Request(int timeoutMs) const;

		void MarkAsNoLongerNeeded() const;

	private:
		Hash hash {0x0};
	};
}
