#pragma once
#include <string>

#include "Entity.h"

namespace ModAPI
{
	class Bone
	{
	public:
		Bone(const Entity& entity, const std::string& boneName);

		[[nodiscard]] static bool IsValid(const Entity& entity, const std::string& boneName);
		
		[[nodiscard]] bool IsValid() const;
		[[nodiscard]] const std::string& GetName();
		[[nodiscard]] int GetIndex() const;
		[[nodiscard]] MMath::Vector3 GetPosition() const;
		[[nodiscard]] MMath::Vector3 GetRotation() const;

	private:
		Entity entity;
		std::string name;
		int index;
	};
}
