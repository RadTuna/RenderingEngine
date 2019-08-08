#pragma once

#include "Engine/Engine.h"
#include "Engine/Math/RenderMath.h"

class TextureHelper
{
private:

	struct Texture2D
	{
		ColorRGB* colorData;
		int width;
		int height;
	};

public:

	TextureHelper();
	~TextureHelper() = default;

	bool Initialize(const char* filename);
	void Release();

	bool LoadBmp(const char* filename);
	ColorRGB GetPixelUV(Vector2& uv);
	ColorRGB GetPixel(int x, int y);

private:

	Texture2D* mTextureData;

};