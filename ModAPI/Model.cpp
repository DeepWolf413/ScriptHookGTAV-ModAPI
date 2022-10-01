#include "Model.h"

#include <iostream>
#include <natives.h>

#include "Math/Vector3.h"

namespace ModAPI
{
	Model::Model(const std::string& name)
	{ this->hash = MISC::GET_HASH_KEY(name.c_str()); }

	Model::Model(const Hash hash)
	{ this->hash = hash; }

	Hash Model::GetHash() const
	{ return hash; }

	bool Model::IsValid() const
	{ return STREAMING::IS_MODEL_VALID(hash); }

	bool Model::IsInCdImage() const
	{ return STREAMING::IS_MODEL_IN_CDIMAGE(hash); }

	bool Model::IsLoaded() const
	{ return STREAMING::HAS_MODEL_LOADED(hash); }

	bool Model::IsCollisionLoaded() const
	{ return STREAMING::HAS_COLLISION_FOR_MODEL_LOADED(hash); }

	bool Model::IsBoat() const
	{ return VEHICLE::IS_THIS_MODEL_A_BOAT(hash); }

	bool Model::IsPed() const
	{ return STREAMING::IS_MODEL_A_PED(hash); }

	bool Model::IsTrain() const
	{ return VEHICLE::IS_THIS_MODEL_A_TRAIN(hash); }

	bool Model::IsVehicle() const
	{ return STREAMING::IS_MODEL_A_VEHICLE(hash); }

	bool Model::IsHelicopter() const
	{
		return VEHICLE::IS_THIS_MODEL_A_HELI(hash);
	}

	bool Model::IsJetski() const
	{
		return VEHICLE::IS_THIS_MODEL_A_JETSKI(hash);
	}

	bool Model::IsPlane() const
	{
		return VEHICLE::IS_THIS_MODEL_A_PLANE(hash);
	}

	bool Model::IsCar() const
	{
		return VEHICLE::IS_THIS_MODEL_A_CAR(hash);
	}

	bool Model::IsBike() const
	{
		return VEHICLE::IS_THIS_MODEL_A_BIKE(hash);
	}

	bool Model::IsBicycle() const
	{
		return VEHICLE::IS_THIS_MODEL_A_BICYCLE(hash);
	}

	bool Model::IsQuadBike() const
	{
		return VEHICLE::IS_THIS_MODEL_A_QUADBIKE(hash);
	}

	void Model::GetDimensions(MMath::Vector3& minimum, MMath::Vector3& maximum) const
	{
		Vector3 minimumDimensions, maximumDimensions;
		MISC::GET_MODEL_DIMENSIONS(hash, &minimumDimensions, &maximumDimensions);
		minimum = MMath::Vector3::FromSHVector3(minimumDimensions);
		maximum = MMath::Vector3::FromSHVector3(maximumDimensions);
	}

	MMath::Vector3 Model::GetDimensions() const
	{
		MMath::Vector3 min, max;
		GetDimensions(min, max);
		return max - min;
	}

	bool Model::Request() const
	{
		if(!IsValid())
		{
			// TODO: Log error "Failed to request model. The model is invalid.".
			return false;
		}

		STREAMING::REQUEST_MODEL(hash);
		return true;
	}

	bool Model::Request(const int timeoutMs) const
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

	void Model::MarkAsNoLongerNeeded() const
	{ STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash); }
}
