#include "Scaleform.h"

#include "natives.h"

namespace ModAPI::UI
{
	Scaleform::Scaleform()
		: handle(NULL)
	{
	}

	Scaleform::Scaleform(const Scaleform& obj)
		: handle(obj.handle)
	{
	}

	Scaleform::Scaleform(int handle)
		: handle(handle)
	{
	}

	int& Scaleform::Handle()
	{
		return this->handle;
	}

	int Scaleform::GetHandle() const
	{
		return this->handle;
	}

	bool Scaleform::HasLoaded() const
	{
		return GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(this->handle) != 0;
	}

	bool Scaleform::Load(const std::string& scaleformID)
	{
		//this->mScaleformID = scaleformID;

		if (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(this->handle))
		{
			this->handle = GRAPHICS::REQUEST_SCALEFORM_MOVIE(const_cast<PCHAR>(scaleformID.c_str()));
			if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(this->handle))
			{ return true; }

			return false;
		}

		return true;
	}

	void Scaleform::Unload()
	{
		auto& handle = this->handle;
		if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(handle))
			GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&handle);
	}

	void Scaleform::PushFunction(const std::string& function) const
	{
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(this->handle, const_cast<PCHAR>(function.c_str()));
	}
	
	void Scaleform::PushInteger(const int arg)
	{
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg);
	}
	
	void Scaleform::PushBoolean(const bool arg)
	{
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(arg);
	}
	
	void Scaleform::PushFloat(const float arg)
	{
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg);
	}
	
	void Scaleform::PushString(const std::string& arg)
	{
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(const_cast<PCHAR>(arg.c_str()));
	}
	
	void Scaleform::PushString2(const std::string& arg)
	{
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(const_cast<PCHAR>(arg.c_str()));
	}
	
	void Scaleform::PushTextComponent(const std::string& arg)
	{
		PCHAR text = const_cast<PCHAR>(arg.c_str());
		if (HUD::DOES_TEXT_LABEL_EXIST(text))
		{
			GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING(text);
		}
		else
		{
			GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING("STRING");
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		}
		//ADD_TEXT_COMPONENT_INTEGER(-1);
		GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();
	}
	
	void Scaleform::PushRGBA(const MMath::Color& arg)
	{
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.R);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.G);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.B);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.A);
	}
	
	void Scaleform::PushRGB(const MMath::Color& arg)
	{
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.R);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.G);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.B);
	}
	
	void Scaleform::PushVector2(const MMath::Vector2& arg)
	{
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg.X);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg.Y);
	}
	
	void Scaleform::PushVector3(const MMath::Vector3& arg)
	{
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg.X);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg.Y);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg.Z);
	}

	void Scaleform::PopFunction()
	{
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}

	void Scaleform::Render2D(const MMath::Color color) const
	{
		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(this->handle, color.R, color.G, color.B, color.A, 0);
	}
	
	void Scaleform::Render2DScreenSpace(const MMath::Vector2& location, const MMath::Vector2& size, const MMath::Color color) const
	{
		GRAPHICS::DRAW_SCALEFORM_MOVIE(this->handle, location.X, location.Y, size.X, size.Y, color.R, color.G, color.B, color.A, 0);
	}
	
	void Scaleform::Render3D(const MMath::Vector3& position, const MMath::Vector3& rotation, const MMath::Vector3& unk, const MMath::Vector3& scale) const
	{
		GRAPHICS::DRAW_SCALEFORM_MOVIE_3D_SOLID(this->handle, position.X, position.Y, position.Z, rotation.X, rotation.Y, rotation.Z, unk.X, unk.Y, unk.Z, scale.X, scale.Y, scale.Z, 2);
	}
	
	void Scaleform::Render3DAdditive(const MMath::Vector3& position, const MMath::Vector3& rotation, const MMath::Vector3& unk, const MMath::Vector3& scale) const
	{
		GRAPHICS::DRAW_SCALEFORM_MOVIE_3D(this->handle, position.X, position.Y, position.Z, rotation.X, rotation.Y, rotation.Z, unk.X, unk.Y, unk.Z, scale.X, scale.Y, scale.Z, 2);
	}
}
