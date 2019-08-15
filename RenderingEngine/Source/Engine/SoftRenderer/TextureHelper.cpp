
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

	// ∆ƒ¿œ¿« »Æ¿Â¿⁄ »πµÊ.
	int endFile;
	for (int i = 0; ; ++i)
	{
		if (filename[i] == '\0')
		{
			endFile = i;
			break;
		}
	}

	char fileType[4];
	int typeIndex = 0;
	for (int i = endFile - 3; i <= endFile; ++i)
	{
		fileType[typeIndex] = filename[i];
		typeIndex++;
	}

	if (strcmp(fileType, "bmp") == 0)
	{
		Result = LoadBmp(filename);
		if (Result == false)
		{
			delete mTextureData;
			return false;
		}
	}
	else if (strcmp(fileType, "tga") == 0)
	{
		Result = LoadTarga(filename);
		if (Result == false)
		{
			delete mTextureData;
			return false;
		}
	}
	else
	{
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

	mTextureData->colorData = new ColorRGBA[imageSize / 3];
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
			mTextureData->colorData[Index].red = imageData[k + 2]; // Red
			mTextureData->colorData[Index].green = imageData[k + 1]; // Green
			mTextureData->colorData[Index].blue = imageData[k + 0]; // Blue

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

bool TextureHelper::LoadTarga(const char* filename)
{
	FILE* filePtr;
	errno_t err;
	unsigned int fileSize;
	TargaHeader targaHeader;
	BYTE* imageData;

	err = fopen_s(&filePtr, filename, "rb");
	if (err != 0)
	{
		return false;
	}

	fileSize = static_cast<unsigned int>(fread(&targaHeader, 1, sizeof(TargaHeader), filePtr));
	if (fileSize != sizeof(TargaHeader))
	{
		return false;
	}

	if (targaHeader.bpp != 32)
	{
		return false;
	}

	mTextureData->width = static_cast<int>(targaHeader.width);
	mTextureData->height = static_cast<int>(targaHeader.height);

	int imageSize = mTextureData->width * mTextureData->height * 4;

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

	mTextureData->colorData = new ColorRGBA[imageSize / 4];
	if (mTextureData->colorData == nullptr)
	{
		delete[] imageData;
		return false;
	}

	int Index = 0;

	int k = (mTextureData->width * mTextureData->height * 4) - (mTextureData->width * 4);

	for (int i = 0; i < mTextureData->height; ++i)
	{
		for (int j = 0; j < mTextureData->width; ++j)
		{
			mTextureData->colorData[Index].red = imageData[k + 2]; // Red
			mTextureData->colorData[Index].green = imageData[k + 1]; // Green
			mTextureData->colorData[Index].blue = imageData[k + 0]; // Blue
			mTextureData->colorData[Index].alpha = imageData[k + 3]; // Alpha

			k += 4;
			Index++;
		}
		k -= (mTextureData->width * 8);
	}

	if (imageData != nullptr)
	{
		delete[] imageData;
		imageData = nullptr;
	}

	return true;

}

ColorRGBA TextureHelper::GetPixelColor(Vector2& uv)
{
	int x = RenderMath::Clamp<int>(static_cast<int>(std::round(mTextureData->width * uv.X)), 0, mTextureData->width);
	int y = RenderMath::Clamp<int>(static_cast<int>(std::round(mTextureData->height * uv.Y)), 0, mTextureData->height);

	return GetPixelColor(x, y);
}

ColorRGBA TextureHelper::GetPixelColor(int x, int y)
{
	ColorRGBA TempRGB = mTextureData->colorData[mTextureData->width * y + x];
	return TempRGB;
}

