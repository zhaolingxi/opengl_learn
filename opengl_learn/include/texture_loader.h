#pragma once

#include"common.h"

enum TextureType :int {
	Texture_UNDEFINE = 0x00,
	Texture_2D = 0x01, // 0x01
};

class TextureLoader {
public:
	TextureLoader(TextureType type);

	int loadTexture(std::string filePath);

	virtual ~TextureLoader();

private:
	std::map<std::string, int> name_id_map_;
	TextureType type_;
};
