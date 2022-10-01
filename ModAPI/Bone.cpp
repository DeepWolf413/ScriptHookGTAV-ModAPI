#include "Bone.h"

#include <natives.h>

#include "Math/Vector3.h"

namespace ModAPI
{
	Bone::Bone(const Entity& entity, const std::string& boneName)
	{
		if (!this->entity.Exists() || boneName.empty())
		{
			index = -1;
			return;
		}
		
		this->entity = Entity(entity.GetHandle());
		this->name = boneName;
		
		index = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(this->entity.GetHandle(), name.c_str());
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
