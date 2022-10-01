#include "RelationshipGroup.h"

#include <natives.h>

namespace ModAPI
{
    bool RelationshipGroup::Exists(const Hash groupHash)
    { return PED::DOES_RELATIONSHIP_GROUP_EXIST(groupHash); }

    void RelationshipGroup::Create(const std::string& name, Hash* groupHash)
    { PED::ADD_RELATIONSHIP_GROUP(name.c_str(), groupHash); }

    void RelationshipGroup::Remove(const Hash groupHash)
    { PED::REMOVE_RELATIONSHIP_GROUP(groupHash); }

    void RelationshipGroup::SetRelationship(const eRelationship relationship, const Hash relationshipGroup,
                                                    const Hash otherRelationshipGroup)
    { PED::SET_RELATIONSHIP_BETWEEN_GROUPS(relationship, relationshipGroup, otherRelationshipGroup); }

    void RelationshipGroup::ClearRelationship(const eRelationship relationship, const Hash relationshipGroup,
                                                      const Hash otherRelationshipGroup)
    { PED::CLEAR_RELATIONSHIP_BETWEEN_GROUPS(relationship, relationshipGroup, otherRelationshipGroup); }

    eRelationship RelationshipGroup::GetRelationship(const Hash relationshipGroup, const Hash otherRelationshipGroup)
    { return static_cast<eRelationship>(PED::GET_RELATIONSHIP_BETWEEN_GROUPS(relationshipGroup, otherRelationshipGroup)); }
}
