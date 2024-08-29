#pragma once
#include "Entities.h"
#include "QuestManager.h"

class InteractableEntity : public Entity {
public:
	InteractableEntity(const ObjectInfo& info, Level* level_ref);
	Coordinates GetPosition() const override;
	RenderingSet GetRenderingSet() const override;
	void Update() override;
	void Interact() override;
protected:
	void Deserialize(const std::vector<std::string>& extra_info_to_read) override;
	bool is_activated;
	std::size_t quest_index;
	std::vector<std::string> objects_to_refer_to;
	std::string default_message;
	std::string activation_message;
	std::string post_message;
	std::string additional_message;
};

class SerialInteractableEntity : public Entity {
public:
	SerialInteractableEntity(const ObjectInfo& info, Level* level_ref);
	Coordinates GetPosition() const override;
	RenderingSet GetRenderingSet() const override;
	void Update() override;
	void Interact() override;
protected:
	void Deserialize(const std::vector<std::string>& extra_info_to_read) override;
	bool is_activated;
	std::size_t quest_index;
	std::size_t self_index;
	std::string default_message;
	std::string activation_message;
	std::string post_message;
	std::string additional_message;
};

class DoublePressActivationEntity : public SerialInteractableEntity {
public:
	DoublePressActivationEntity(const ObjectInfo& info, Level* level_ref);
	Coordinates GetPosition() const override;
	RenderingSet GetRenderingSet() const override;
	void Update() override;
	void Interact() override;
private:
	void Deserialize(const std::vector<std::string>& extra_info_to_read) override;
};

class SinglePressActivationEntity : public SerialInteractableEntity {
public:
	SinglePressActivationEntity(const ObjectInfo& info, Level* level_ref);
	Coordinates GetPosition() const override;
	RenderingSet GetRenderingSet() const override;
	void Update() override;
	void Interact() override;
private:
	void Deserialize(const std::vector<std::string>& extra_info_to_read) override;
};

class Door : public Entity {
public:
	Door(const ObjectInfo& info, Level* level_ref);
	Coordinates GetPosition() const override;
	RenderingSet GetRenderingSet() const override;
	void Update() override;
	void Interact() override;
private:
	void Deserialize(const std::vector<std::string>& extra_info_to_read) override;
	std::string level_name;
	bool is_locked;
	std::size_t quest_index;
	std::string default_message;
	std::string activation_message;
	std::string post_message;
	std::string additional_message;
};

class Readable : public Entity {
public:
	Readable(const ObjectInfo& info, Level* level_ref);
	Coordinates GetPosition() const override;
	RenderingSet GetRenderingSet() const override;
	void Update() override;
	void Interact() override;
private:
	void Deserialize(const std::vector<std::string>& extra_info_to_read) override;
	std::string default_message;
};
