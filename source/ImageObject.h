#pragma once
#include "Object.h"
#include "ImageRenderer.h"

class ImageObject : public Object
{
public:
	ImageObject(std::string texturePath, Vector2 sourceOffset, Vector2 sourceSize) : Object()
	{
		_renderer = new ImageRenderer(_transform.get(), texturePath, sourceOffset, sourceSize);
	}

	void SetTexture(const std::string& path)
	{
		static_cast<ImageRenderer*>(_renderer)->SetTexture(path);
	}

};