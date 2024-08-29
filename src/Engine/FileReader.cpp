#include "FileReader.h"

std::string FileReader::directory;

sf::Texture FileReader::ReadSpriteFile(const std::string& file_to_read) {
	sf::Texture sprite_image = {};
	std::string file = directory + file_to_read;
	sprite_image.loadFromFile(file);
	return sprite_image;
}

LevelTiles FileReader::ReadTileFile(const std::string& file_to_read) {
	std::string file_name = directory + file_to_read;
	std::ifstream file  {file_name, file.in };
	assert(file.is_open());
	std::size_t width = 0;
	file >> width;
	char tile = 0;
	std::vector<char> tiles_to_convert{};
	while (!file.eof()) {
		file >> tile;
		tiles_to_convert.push_back(tile);
	}
	tiles_to_convert.pop_back();
	file.close();
	std::vector<TileType> converted_tiles{};
	for (auto t : tiles_to_convert) {
		if (t == '-' || t == '+') {
			converted_tiles.push_back(TileType{ true, nullptr });
		}
		else converted_tiles.push_back(TileType{ false, nullptr });
	}
	return LevelTiles{ width, converted_tiles };
}

std::vector<ObjectInfo> FileReader::ReadLevelFile(const std::string& file_to_read) {
	std::vector<ObjectInfo> factory_bunch {};
	std::string file_name = directory + file_to_read;
	std::ifstream file {file_name, file.in };
	assert(file.is_open());
	while (!file.eof()) {
		char object_type = 0;
		file >> object_type;
		std::string sprite_file_name{}, collision_file_name{}, to_process{};
		char interactable_type = 0;
		std::size_t quantity = 0, occupied_tiles = 0, height = 0;
		std::vector<Coordinates> coordinates{};
		std::vector<std::string> extra_info{};
		float x = 0, y = 0;
		switch (object_type) {
		case 'L': 
			file >> sprite_file_name >> collision_file_name;
			factory_bunch.push_back(ObjectInfo{ sprite_file_name, collision_file_name, std::vector<Coordinates>{Coordinates{0, 0}}, SpriteType::level_sprite});
			sprite_file_name.clear();
			collision_file_name.clear();
			break;
		case 'S':
			file >> quantity;
			while (quantity != 0) {
				file >> sprite_file_name >> occupied_tiles;
				if (occupied_tiles == 1) {
					file >> x >> y;
					coordinates.push_back(Coordinates{ x,y });
				}
				else {
					while (occupied_tiles > 0) {
						file >> x >> y;
						coordinates.push_back(Coordinates{ x,y });
						occupied_tiles--;
					}
				}
				file >> height;
				coordinates.front().z = height;
				factory_bunch.push_back(ObjectInfo{ sprite_file_name, std::string{}, coordinates, SpriteType::static_sprite});
				sprite_file_name.clear();
				coordinates.clear();
				quantity--;
			}
			break;
		case 'I':
			file >> quantity;
			while (quantity != 0) {
				file >> sprite_file_name >> occupied_tiles;
				if (occupied_tiles == 1) {
					file >> x >> y;
					coordinates.push_back(Coordinates{ x,y });
				}
				else {
					while (occupied_tiles > 0) {
						file >> x >> y;
						coordinates.push_back(Coordinates{ x,y });
						occupied_tiles--;
					}
				}
				file >> height;
				coordinates.front().z = height;
				while (true) {
					file >> to_process;
					extra_info.push_back(to_process);
					if (to_process.back() == '$') break;
					to_process.pop_back();
					to_process.clear();
				}
				factory_bunch.push_back(ObjectInfo{ sprite_file_name, std::string{}, coordinates, SpriteType::interactable_sprite, extra_info });
				sprite_file_name.clear();
				coordinates.clear();
				to_process.clear();
				extra_info.clear();
				quantity--;
			}
			break;
		case 'P':
			file >> x >> y >> height;
			factory_bunch.push_back(ObjectInfo{ std::string{}, std::string{}, std::vector<Coordinates>{Coordinates{x, y, height}}, SpriteType::player_sprite});
			sprite_file_name.clear();
		}
	}
	if (factory_bunch[factory_bunch.size() - 1].sprite_type == SpriteType::player_sprite && factory_bunch[factory_bunch.size() - 2].sprite_type == SpriteType::player_sprite) factory_bunch.pop_back();
	file.close();
	return factory_bunch;
}

std::string FileReader::ReadTextFile(const std::string& file_to_read) {
	std::string file_name = directory + file_to_read;
	std::ifstream file {file_name, file.in };
	assert(file.is_open());
	std::size_t lines_to_read;
	file >> lines_to_read;
	std::string text{};
	while (lines_to_read > 0) {
		std::string buffer{};
		std::getline(file, buffer);
		text += buffer + "\n";
		buffer.clear();
		lines_to_read--;
	}
	return text;
}

sf::Font FileReader::ReadFontFile(const std::string& file_to_read) {
	sf::Font font = {};
	std::string file = directory + file_to_read;
	font.loadFromFile(file);
	return font;
}


void FileReader::SetDirectory(const std::string& dir_name_to_set) {
	directory = dir_name_to_set;
}