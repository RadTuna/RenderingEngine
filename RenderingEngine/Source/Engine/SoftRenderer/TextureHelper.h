#pragma once

#include "Engine/Engine.h"
#include "Engine/Math/RenderMath.h"

class TextureHelper
{
private:

	struct Texture2D
	{
		ColorRGBA* colorData;
		int width;
		int height;
	};

	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};

public:

	TextureHelper();
	~TextureHelper() = default;

	bool Initialize(const char* filename);
	void Release();

	bool LoadBmp(const char* filename);
	bool LoadTarga(const char* filename);
	ColorRGBA GetPixelColor(Vector2& uv);
	ColorRGBA GetPixelColor(int x, int y);

private:

	Texture2D* mTextureData;

};