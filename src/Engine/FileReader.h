#pragma once

#include <fstream>
#include <cassert>
#include "Utilities.h"
#include "Entities.h"


class FileReader {
public:
	FileReader() = default;
	static sf::Texture ReadSpriteFile(const std::string& file_to_read);
	static LevelTiles ReadTileFile(const std::string& file_to_read);
	static std::vector<ObjectInfo> ReadLevelFile(const std::string& file_to_read);
	static std::string ReadTextFile(const std::string& file_to_read);
	static sf::Font ReadFontFile(const std::string& file_to_read);
	static void SetDirectory(const std::string& dir_name_to_set);
private:
	static std::string directory;
};