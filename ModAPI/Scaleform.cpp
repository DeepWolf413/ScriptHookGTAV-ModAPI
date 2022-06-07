#include "Scaleform.h"

#include "shsdk/natives.h"

ModAPI::Scaleform::Scaleform()
{
}

ModAPI::Scaleform::Scaleform(const Scaleform& obj)
	: mHandle(obj.mHandle)
{
}

ModAPI::Scaleform::Scaleform(int handle)
	: mHandle(handle)
{
}

int& ModAPI::Scaleform::Handle()
{
	return this->mHandle;
}

int ModAPI::Scaleform::GetHandle() const
{
	return this->mHandle;
}

bool ModAPI::Scaleform::HasLoaded() const
{
	return GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(this->mHandle) != 0;
}

bool ModAPI::Scaleform::Load(const std::string& scaleformID)
{
	//this->mScaleformID = scaleformID;

	if (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(this->mHandle))
	{
		this->mHandle = GRAPHICS::REQUEST_SCALEFORM_MOVIE(const_cast<PCHAR>(scaleformID.c_str()));
		if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(this->mHandle))
		{ return true; }

		return false;
	}

	return true;
}

void ModAPI::Scaleform::Unload()
{
	auto& handle = this->mHandle;
	if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(handle))
		GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&handle);
}

void ModAPI::Scaleform::PushFunction(const std::string& function) const
{
	GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(this->mHandle, const_cast<PCHAR>(function.c_str()));
}
void ModAPI::Scaleform::PushInteger(const int arg)
{
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg);
}
void ModAPI::Scaleform::PushBoolean(const bool arg)
{
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(arg);
}
void ModAPI::Scaleform::PushFloat(const float arg)
{
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg);
}
void ModAPI::Scaleform::PushString(const std::string& arg)
{
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(const_cast<PCHAR>(arg.c_str()));
}
void ModAPI::Scaleform::PushString2(const std::string& arg)
{
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(const_cast<PCHAR>(arg.c_str()));
}
void ModAPI::Scaleform::PushTextComponent(const std::string& arg)
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
void ModAPI::Scaleform::PushRGBA(const Color& arg)
{
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.R);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.G);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.B);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.A);
}
void ModAPI::Scaleform::PushRGB(const Color& arg)
{
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.R);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.G);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(arg.B);
}
void ModAPI::Scaleform::PushVector2(const Vector2& arg)
{
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg.X);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg.Y);
}
void ModAPI::Scaleform::PushVector3(const Vector3& arg)
{
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg.X);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg.Y);
	GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(arg.Z);
}

void ModAPI::Scaleform::PopFunction()
{
	GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
}


void ModAPI::Scaleform::Render2D(const Color color) const
{
	GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(this->mHandle, color.R, color.G, color.B, color.A, 0);
}
void ModAPI::Scaleform::Render2DScreenSpace(const Vector2& location, const Vector2& size, const Color color) const
{
	GRAPHICS::DRAW_SCALEFORM_MOVIE(this->mHandle, location.X, location.Y, size.X, size.Y, color.R, color.G, color.B, color.A, 0);
}
void ModAPI::Scaleform::Render3D(const Vector3& position, const Vector3& rotation, const Vector3& unk, const Vector3& scale) const
{
	GRAPHICS::DRAW_SCALEFORM_MOVIE_3D_SOLID(this->mHandle, position.X, position.Y, position.Z, rotation.X, rotation.Y, rotation.Z, unk.X, unk.Y, unk.Z, scale.X, scale.Y, scale.Z, 2);
}
void ModAPI::Scaleform::Render3DAdditive(const Vector3& position, const Vector3& rotation, const Vector3& unk, const Vector3& scale) const
{
	GRAPHICS::DRAW_SCALEFORM_MOVIE_3D(this->mHandle, position.X, position.Y, position.Z, rotation.X, rotation.Y, rotation.Z, unk.X, unk.Y, unk.Z, scale.X, scale.Y, scale.Z, 2);
}
