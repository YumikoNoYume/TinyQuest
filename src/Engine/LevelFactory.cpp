#include "LevelFactory.h"

LevelFactory::LevelFactory(std::unordered_map<char, std::function<WorldObject*(ObjectInfo, Level*)>> constructors, InputManager& input, const std::string& player_sprite) : 
	player(Player{ ObjectInfo{player_sprite, std::string{}, std::vector<Coordinates>{Coordinates{0, 0, 2}}}, nullptr, input }),
	constructors(constructors) {}

LevelFactory::~LevelFactory() {
	for (auto level : levels) {
		for (auto element : level.second) {
			delete element;
		}
	}
}

Player& LevelFactory::GetPlayer() {
	return player;
}

void LevelFactory::Update(const std::string& level_to_update) {
	auto result = levels.find(level_to_update);
	if (result != levels.end()) {
		for (auto entity : result->second) {
			entity->Update();
		}
	}
	LoadLevel(LevelSwitcher::GetInst().GetLevel());
}

void LevelFactory::LoadLevel(const std::string& level_to_load) {
	auto result = levels.find(level_to_load);
	if (result != levels.end()) return;
	std::vector<WorldObject*> level_objects{};
	std::string file_name {level_to_load};
	std::vector<ObjectInfo> objects = FileReader::ReadLevelFile(file_name);
	for (auto obj : objects) {
		if (obj.sprite_type == SpriteType::level_sprite) {
			WorldObject* level = new Level{ obj };
			level_objects.push_back(level);
		}
		else if (obj.sprite_type == SpriteType::static_sprite) {
			WorldObject* entity = new Entity{ obj, static_cast<Level*>(level_objects.front()) };
			level_objects.push_back(entity);
		}
		else if (obj.sprite_type == SpriteType::interactable_sprite) {
			WorldObject* entity = constructors.find(obj.extra_info.front().front())->second(obj, static_cast<Level*>(level_objects.front()));
			level_objects.push_back(entity);
		}
		else {
			player.MoveToNewLevel(static_cast<Level*>(level_objects.front()));
			player.SetNewPosition(obj.coordinates.front());
			WorldObject* entity = new Player{ player };
			level_objects.push_back(entity);
		}
	}
	levels.insert({ level_to_load, level_objects });
}

std::vector<WorldObject*> LevelFactory::GetLevelObjects(const std::string& level_to_check) {
	auto result = levels.find(level_to_check);
	assert(result != levels.end());
	return result->second;
}
