#pragma once
#include <enums.h>
#include <string>
#include <types.h>

namespace ModAPI::RelationshipGroup
{
	bool Exists(Hash groupHash);
	void Create(const std::string& name, Hash* groupHash);
	void Remove(Hash groupHash);
	void SetRelationship(eRelationship relationship, Hash relationshipGroup, Hash otherRelationshipGroup);
	void ClearRelationship(eRelationship relationship, Hash relationshipGroup, Hash otherRelationshipGroup);
	eRelationship GetRelationship(Hash relationshipGroup, Hash otherRelationshipGroup);
}