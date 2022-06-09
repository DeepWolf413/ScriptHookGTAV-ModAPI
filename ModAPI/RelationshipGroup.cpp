#include "RelationshipGroup.h"

#include "shsdk/natives.h"

bool ModAPI::RelationshipGroup::Exists(const Hash groupHash)
{ return PED::_DOES_RELATIONSHIP_GROUP_EXIST(groupHash); }

void ModAPI::RelationshipGroup::Create(const std::string& name, Hash* groupHash)
{ PED::ADD_RELATIONSHIP_GROUP(name.c_str(), groupHash); }

void ModAPI::RelationshipGroup::Remove(const Hash groupHash)
{ PED::REMOVE_RELATIONSHIP_GROUP(groupHash); }

void ModAPI::RelationshipGroup::SetRelationship(const eRelationship relationship, const Hash relationshipGroup,
                                                const Hash otherRelationshipGroup)
{ PED::SET_RELATIONSHIP_BETWEEN_GROUPS(relationship, relationshipGroup, otherRelationshipGroup); }

void ModAPI::RelationshipGroup::ClearRelationship(const eRelationship relationship, const Hash relationshipGroup,
                                                  const Hash otherRelationshipGroup)
{ PED::CLEAR_RELATIONSHIP_BETWEEN_GROUPS(relationship, relationshipGroup, otherRelationshipGroup); }

eRelationship ModAPI::RelationshipGroup::GetRelationship(const Hash relationshipGroup, const Hash otherRelationshipGroup)
{ return static_cast<eRelationship>(PED::GET_RELATIONSHIP_BETWEEN_GROUPS(relationshipGroup, otherRelationshipGroup)); }
