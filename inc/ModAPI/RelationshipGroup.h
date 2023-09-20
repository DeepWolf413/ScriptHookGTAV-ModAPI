#pragma once
#include <enums.h>
#include <string>
#include <types.h>

namespace ModAPI::RelationshipGroup
{
	bool Exists(Hash relationshipGroupHash);
	void Create(const std::string& name, Hash* relationshipGroupHash);
	void Remove(Hash relationshipGroupHash);
	void SetRelationship(eRelationship newRelationship, Hash relationshipGroup, Hash otherRelationshipGroup, bool bidirectionally = false);
	void ClearRelationship(eRelationship relationship, Hash relationshipGroup, Hash otherRelationshipGroup, bool bidirectionally = false);
	eRelationship GetRelationship(Hash relationshipGroup, Hash otherRelationshipGroup);
}