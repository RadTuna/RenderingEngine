
#include "TextureHelper.h"


TextureHelper::TextureHelper()
{
	mTextureData = nullptr;
}

bool TextureHelper::Initialize(const char* filename)
{
	bool Result;

	mTextureData = new Texture2D;
	if (mTextureData == nullptr)
	{
		return false;
	}

	Result = LoadBmp(filename);
	if (Result == false)
	{
		delete mTextureData;
		return false;
	}

	return true;
}

void TextureHelper::Release()
{
	if (mTextureData->colorData != nullptr)
	{
		delete[] mTextureData->colorData;
		mTextureData->colorData = nullptr;
	}

	if (mTextureData != nullptr)
	{
		delete mTextureData;
		mTextureData = nullptr;
	}
}

bool TextureHelper::LoadBmp(const char* filename)
{
	FILE* filePtr;
	errno_t err;
	unsigned int fileSize;
	BITMAPINFOHEADER bmpHeader;
	BITMAPFILEHEADER bmpFileHeader;
	BYTE* imageData;

	err = fopen_s(&filePtr, filename, "rb");
	if (err != 0)
	{
		return false;
	}

	fileSize = static_cast<unsigned int>(fread(&bmpFileHeader, 1, sizeof(BITMAPFILEHEADER), filePtr));
	if (fileSize != sizeof(BITMAPFILEHEADER))
	{
		return false;
	}

	fileSize = static_cast<unsigned int>(fread(&bmpHeader, 1, sizeof(BITMAPINFOHEADER), filePtr));
	if (fileSize != sizeof(BITMAPINFOHEADER))
	{
		return false;
	}

	mTextureData->width = static_cast<int>(bmpHeader.biWidth);
	mTextureData->height = static_cast<int>(bmpHeader.biHeight);

	int imageSize = mTextureData->width * mTextureData->height * 3;

	imageData = new BYTE[imageSize];
	if (imageData == nullptr)
	{
		return false;
	}

	fileSize = static_cast<unsigned int>(fread(imageData, 1, imageSize, filePtr));
	if (fileSize != imageSize)
	{
		delete[] imageData;
		return false;
	}

	err = fclose(filePtr);
	if (err != 0)
	{
		delete[] imageData;
		return false;
	}

	mTextureData->colorData = new ColorRGB[imageSize / 3];
	if (mTextureData->colorData == nullptr)
	{
		delete[] imageData;
		return false;
	}

	int Index = 0;

	int k = (mTextureData->width * mTextureData->height * 3) - (mTextureData->width * 3);

	for (int i = 0; i < mTextureData->height; ++i)
	{
		for (int j = 0; j < mTextureData->width; ++j)
		{
			mTextureData->colorData[Index].Red = imageData[k + 2]; // Red
			mTextureData->colorData[Index].Green = imageData[k + 1]; // Green
			mTextureData->colorData[Index].Blue = imageData[k + 0]; // Blue

			k += 3;
			Index++;
		}
		k -= (mTextureData->width * 6);
	}

	if (imageData != nullptr)
	{
		delete[] imageData;
		imageData = nullptr;
	}

	return true;
}

ColorRGB TextureHelper::GetPixelUV(Vector2 uv)
{
	int x = static_cast<int>(mTextureData->width * uv.X);
	int y = static_cast<int>(mTextureData->height * uv.Y);

	return GetPixel(x, y);
}

ColorRGB TextureHelper::GetPixel(int x, int y)
{
	ColorRGB TempRGB = mTextureData->colorData[mTextureData->width * y + x];
	return TempRGB;
}

