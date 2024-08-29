#pragma once

#include <vector>
#include <string>
#include "Utilities.h"
#include "InputManager.h"
#include "TextManager.h"

class WorldObject {
public:
	WorldObject(const ObjectInfo& info);
	virtual ~WorldObject() = default;
	virtual Coordinates GetPosition() const = 0;
	virtual RenderingSet GetRenderingSet() const = 0;
	virtual void Update() = 0;
	virtual void Interact() = 0;
protected:
	virtual void Deserialize(const std::vector<std::string>& extra_info_to_read) = 0;
	sf::Texture sprite_image;
	std::vector<Coordinates> current_position;
};

class Level : public WorldObject {
public:
	Level(const ObjectInfo& info);
	Coordinates GetPosition() const override;
	RenderingSet GetRenderingSet() const override;
	void Update() override;
	void Interact() override;
	bool GetTileType(Coordinates coordinates_to_check) const;
	void SetInteractableObject(WorldObject* object_to_set, Coordinates coordinates_to_set);
	WorldObject* Level::GetObject(Coordinates coordinates_to_check);
private:
	void Deserialize(const std::vector<std::string>& extra_info_to_read) override;
	std::vector<std::vector<TileType>> level_tiles_grid;
};

class Entity : public WorldObject {
public:
	Entity(const ObjectInfo& info, Level* level_ref);
	Coordinates GetPosition() const override;
	RenderingSet GetRenderingSet() const override;
	void Update() override;
	void Interact() override;
protected:
	void Deserialize(const std::vector<std::string>& extra_info_to_read) override;
	Level* level;
};

class Player : public Entity {
public:
	Player(const ObjectInfo& info, Level* level_ref, InputManager& input);
	Coordinates GetPosition() const override;
	RenderingSet GetRenderingSet() const override;
	void Update() override;
	void Interact() override;
	void MoveToNewLevel(Level* level_to_move_to);
	void SetNewPosition(Coordinates coordinates_to_set);
private:
	void Deserialize(const std::vector<std::string>& extra_info_to_read) override;
	void SetCoordinates(Coordinates coordinates_to_set);
	InputManager& input_manager;
};

