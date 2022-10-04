#include "Bone.h"

#include <natives.h>

#include "Logger.h"
#include "MathAPI.h"

namespace ModAPI
{
	Bone::Bone(const Entity& entity, const std::string& boneName)
	{
		if (!entity.Exists() || boneName.empty())
		{
			index = -1;
			name = boneName;
			Logging::Logger::TryLogWarning(
				"[Bone] Failed to initialize bone '" + boneName +
				"'. The entity doesn't exist, or the bone name is invalid.");
			return;
		}

		this->entity = Entity(entity.GetHandle());
		name = boneName;

		index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(this->entity.GetHandle(), name.c_str());

		if (!IsValid())
		{
			Logging::Logger::TryLogWarning(
				"[Bone] Failed to initialize bone '" + boneName + "'. The bone name might be invalid.");
		}
	}

	bool Bone::IsValid(const Entity& entity, const std::string& boneName)
	{
		return ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(entity.GetHandle(), boneName.c_str()) != -1;
	}

	bool Bone::IsValid() const
	{
		return this->entity.Exists() && index != -1;
	}

	const std::string& Bone::GetName()
	{
		return name;
	}

	int Bone::GetIndex() const
	{
		return index;
	}

	MMath::Vector3 Bone::GetPosition() const
	{
		if (!entity.Exists())
		{
			return {};
		}

		return MMath::Vector3::FromSHVector3(ENTITY::GET_ENTITY_BONE_POSTION(entity.GetHandle(), index));
	}

	MMath::Vector3 Bone::GetRotation() const
	{
		if (!entity.Exists())
		{
			return {};
		}
		
		return MMath::Vector3::FromSHVector3(ENTITY::GET_ENTITY_BONE_ROTATION(entity.GetHandle(), index));
	}
}
