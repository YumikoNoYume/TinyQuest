#pragma once

#include <unordered_map>
#include <functional>
#include <cassert>
#include "FileReader.h"
#include "InputManager.h"

class LevelFactory {
public:
	LevelFactory(std::unordered_map<char, std::function<WorldObject*(ObjectInfo, Level*)>> constructors, InputManager& input, const std::string& player_sprite);
	~LevelFactory();
	std::vector<WorldObject*> GetLevelObjects(const std::string& level_to_check);
	void Update(const std::string& level_to_update);
	void LoadLevel(const std::string& level_to_load);
	Player& GetPlayer();
private:
	std::unordered_map<std::string, std::vector<WorldObject*>> levels;
	std::unordered_map<char, std::function<WorldObject*(ObjectInfo, Level*)>> constructors;
	Player player;
};