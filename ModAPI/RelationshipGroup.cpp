#include "RelationshipGroup.h"

#include <natives.h>

namespace ModAPI
{
    bool RelationshipGroup::Exists(const Hash relationshipGroupHash)
    { return PED::DOES_RELATIONSHIP_GROUP_EXIST(relationshipGroupHash); }

    void RelationshipGroup::Create(const std::string& name, Hash* relationshipGroupHash)
    { PED::ADD_RELATIONSHIP_GROUP(name.c_str(), relationshipGroupHash); }

    void RelationshipGroup::Remove(const Hash relationshipGroupHash)
    { PED::REMOVE_RELATIONSHIP_GROUP(relationshipGroupHash); }

    void RelationshipGroup::SetRelationship(const eRelationship newRelationship, const Hash relationshipGroup, const Hash otherRelationshipGroup, const bool bidirectionally)
    {
        PED::SET_RELATIONSHIP_BETWEEN_GROUPS(newRelationship, relationshipGroup, otherRelationshipGroup);

        if (bidirectionally)
        {
            PED::SET_RELATIONSHIP_BETWEEN_GROUPS(newRelationship, otherRelationshipGroup, relationshipGroup);
        }
    }

    void RelationshipGroup::ClearRelationship(const eRelationship relationship, const Hash relationshipGroup, const Hash otherRelationshipGroup, bool bidirectionally)
    {
        PED::CLEAR_RELATIONSHIP_BETWEEN_GROUPS(relationship, relationshipGroup, otherRelationshipGroup);

        if (bidirectionally)
        {
            PED::CLEAR_RELATIONSHIP_BETWEEN_GROUPS(relationship, otherRelationshipGroup, relationshipGroup);
        }
    }

    eRelationship RelationshipGroup::GetRelationship(const Hash relationshipGroup, const Hash otherRelationshipGroup)
    { return static_cast<eRelationship>(PED::GET_RELATIONSHIP_BETWEEN_GROUPS(relationshipGroup, otherRelationshipGroup)); }
}
