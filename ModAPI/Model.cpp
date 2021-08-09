#include "Model.h"

#include <iostream>



#include <shsdk/natives.h>
#include "math/Vector3.h"

ModAPI::Model::Model(const std::string name)
{ this->hash = MISC::GET_HASH_KEY(name.c_str()); }

ModAPI::Model::Model(const Hash hash)
{ this->hash = hash; }

Hash ModAPI::Model::GetHash() const
{ return hash; }

bool ModAPI::Model::IsValid() const
{ return STREAMING::IS_MODEL_VALID(hash); }

bool ModAPI::Model::IsInCdImage() const
{ return STREAMING::IS_MODEL_IN_CDIMAGE(hash); }

bool ModAPI::Model::IsLoaded() const
{ return STREAMING::HAS_MODEL_LOADED(hash); }

bool ModAPI::Model::IsCollisionLoaded() const
{ return STREAMING::HAS_COLLISION_FOR_MODEL_LOADED(hash); }

bool ModAPI::Model::IsBoat() const
{ return VEHICLE::IS_THIS_MODEL_A_BOAT(hash); }

bool ModAPI::Model::IsPed() const
{ return STREAMING::IS_MODEL_A_PED(hash); }

bool ModAPI::Model::IsTrain() const
{ return VEHICLE::IS_THIS_MODEL_A_TRAIN(hash); }

bool ModAPI::Model::IsVehicle() const
{ return STREAMING::IS_MODEL_A_VEHICLE(hash); }

void ModAPI::Model::GetDimensions(Vector3* minimum, Vector3* maximum) const
{ MISC::GET_MODEL_DIMENSIONS(hash, minimum, maximum); }

Vector3 ModAPI::Model::GetDimensions() const
{
	Vector3 min, max;
	GetDimensions(&min, &max);
	return Vector3::Subtract(max, min);
}

bool ModAPI::Model::Request() const
{
	if(!IsValid())
	{
		// TODO: Log error "Failed to request model. The model is invalid.".
		return false;
	}

	STREAMING::REQUEST_MODEL(hash);
	return true;
}

bool ModAPI::Model::Request(const int timeoutMs) const
{
	if(!Request())
	{ return false; }

	int msPassed = 0;
	while(!IsLoaded())
	{
		WAIT(1);

		msPassed++;
		if(msPassed >= timeoutMs)
		{
			// TODO: Log error "Failed to request model. Timeout.".
			return false;
		}
	}

	MarkAsNoLongerNeeded();
	return true;
}

void ModAPI::Model::MarkAsNoLongerNeeded() const
{ STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash); }