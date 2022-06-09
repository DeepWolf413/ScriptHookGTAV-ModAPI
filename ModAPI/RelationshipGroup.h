#pragma once
#include <string>

#include "shsdk/enums.h"
#include "shsdk/types.h"

namespace ModAPI
{
	namespace RelationshipGroup
	{
		bool Exists(Hash groupHash);
		void Create(const std::string& name, Hash* groupHash);
		void Remove(Hash groupHash);
		void SetRelationship(eRelationship relationship, Hash relationshipGroup, Hash otherRelationshipGroup);
		void ClearRelationship(eRelationship relationship, Hash relationshipGroup, Hash otherRelationshipGroup);
		eRelationship GetRelationship(Hash relationshipGroup, Hash otherRelationshipGroup);
	}
};
