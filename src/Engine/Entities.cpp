#include "Entities.h"

WorldObject::WorldObject(const ObjectInfo& info) {
	sprite_image = FileReader::ReadSpriteFile(info.sprite_file_name);
	current_position = info.coordinates;
}

Level::Level(const ObjectInfo& info) : WorldObject(info) {
	LevelTiles level = FileReader::ReadTileFile(info.collision_file_name);
	auto it = level.level_tiles.begin();
	while (it != level.level_tiles.end()) {
		level_tiles_grid.push_back(std::vector<TileType>{it, it + level.level_width});
		it = it == level.level_tiles.end() ? it : it + level.level_width;
	}
}

Coordinates Level::GetPosition() const {
	return current_position.front();
}

RenderingSet Level::GetRenderingSet() const {
	return RenderingSet{ Sprite{sprite_image, sf::Sprite{}}, current_position.front(), SpriteType::level_sprite, 1};
}

void Level::Update() {} 

void Level::Interact() {}

bool Level::GetTileType(Coordinates coordinates_to_check) const {
	return level_tiles_grid[coordinates_to_check.y][coordinates_to_check.x].is_obstacle;
}

void Level::SetInteractableObject(WorldObject* object_to_set, Coordinates coordinates_to_set) {
	level_tiles_grid[coordinates_to_set.y][coordinates_to_set.x].interactable_object = object_to_set;
}

WorldObject* Level::GetObject(Coordinates coordinates_to_check) {
	return level_tiles_grid[coordinates_to_check.y][coordinates_to_check.x].interactable_object;
}

void Level::Deserialize(const std::vector<std::string>& extra_info_to_read) {}

Entity::Entity(const ObjectInfo& info, Level* level_ref) : WorldObject(info), level(level_ref) {}

Coordinates Entity::GetPosition() const {
	return current_position.front();
}

RenderingSet Entity::GetRenderingSet() const {
	return RenderingSet{ Sprite{sprite_image, sf::Sprite{}}, GetPosition(), SpriteType::static_sprite, GetPosition().z};
}

void Entity::Update() {}

void Entity::Interact() {}
 
void Entity::Deserialize(const std::vector<std::string>& extra_info_to_read) {}

Player::Player(const ObjectInfo& info, Level* level_ref, InputManager& input) : Entity(info, level_ref), input_manager(input) {}

Coordinates Player::GetPosition() const {
	return Entity::GetPosition();
}

RenderingSet Player::GetRenderingSet() const {
	return RenderingSet{ Sprite{sprite_image, sf::Sprite{}}, GetPosition(), SpriteType::player_sprite, GetPosition().z};
}

void Player::Update() {
	WorldObject* object = nullptr;
	char key = input_manager.GetLastKey();
	Coordinates current = GetPosition();
	switch (key) {
	case 'a':
		current.x -= 1;
		SetNewPosition(current);
		break;
	case 'd':
		current.x += 1;
		SetNewPosition(current);
		break;
	case 's':
		current.y += 1;
		SetNewPosition(current);
		break;
	case 'w':
		current.y -= 1;
		SetNewPosition(current);
		break;
	case 'e':
		object = level->GetObject(Coordinates{ current_position.front().x, current_position.front().y - 1 });
		if (object != nullptr) {
			object->Interact();
			break;
		}
		object = level->GetObject(Coordinates{ current_position.front().x - 1, current_position.front().y });
		if (object != nullptr) {
			object->Interact();
			break;
		}
		object = level->GetObject(Coordinates{ current_position.front().x + 1, current_position.front().y });
		if (object != nullptr) {
			object->Interact();
			break;
		}
		object = level->GetObject(Coordinates{ current_position.front().x, current_position.front().y + 1 });
		if (object != nullptr) {
			object->Interact();
			break;
		}
		break;
	case '/':
		break;
	}
}

void Player::Interact() {}

void Player::MoveToNewLevel(Level* level_to_move_to) {
	level = level_to_move_to;
}

void Player::SetNewPosition(Coordinates coordinates_to_set) {
	if (level->GetTileType(Coordinates{ coordinates_to_set.x, coordinates_to_set.y })) return;
	SetCoordinates(coordinates_to_set);
}

void Player::SetCoordinates(Coordinates coordinates_to_set) {
	current_position.front() = coordinates_to_set;
}

void Player::Deserialize(const std::vector<std::string>& extra_info_to_read) {}

