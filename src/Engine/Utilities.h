#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>

class LevelSwitcher {
public:
	static LevelSwitcher& GetInst();
	void SetLevel(const std::string& level_to_set);
	std::string GetLevel() const;
	bool IsGameFinished() const;
	void FinishGame();
private:
	LevelSwitcher() = default;
	std::string current_level;
	bool is_finished = false;
};

class WorldObject;

struct TileType {
	bool is_obstacle = false;
	WorldObject* interactable_object = nullptr;
};

struct LevelTiles {
	std::size_t level_width;
	std::vector<TileType> level_tiles;
};

struct Coordinates {
	float x = 0;
	float y = 0;
	std::size_t z = 0;
};

enum class SpriteType { static_sprite, interactable_sprite, level_sprite, player_sprite, text };

struct Sprite {
	sf::Texture texture;
	sf::Sprite sprite;
};

struct Message {
	sf::Font font;
	std::string text;
	size_t size;
	sf::Text message;
	sf::Color color;
};

struct RenderingSet {
	Sprite sprite;
	Coordinates coordinates;
	SpriteType sprite_type;
	std::size_t sprite_height;
	Message message;
};

struct ObjectInfo {
	std::string sprite_file_name;
	std::string collision_file_name;
	std::vector<Coordinates> coordinates;
	SpriteType sprite_type;
	std::vector<std::string> extra_info;
};