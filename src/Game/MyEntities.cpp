#include "MyEntities.h"

InteractableEntity::InteractableEntity(const ObjectInfo& info, Level* level_ref) : Entity(info, level_ref) {
	Deserialize(info.extra_info);
	for (std::size_t index = 0; index < current_position.size(); index++) {
		level_ref->SetInteractableObject(this, current_position[index]);
	}
}

void InteractableEntity::Deserialize(const std::vector<std::string>& extra_info_to_read) {
	is_activated = false;
	std::size_t index = 1;
	quest_index = std::stoll(extra_info_to_read[index]);
	int quantity = std::stoll(extra_info_to_read[++index]);
	while (quantity > 0) {
		objects_to_refer_to.push_back(extra_info_to_read[++index]);
		quantity--;
	}
	quantity = std::stoll(extra_info_to_read[++index]);
	default_message = extra_info_to_read[++index];
	activation_message = --quantity > 0 ? extra_info_to_read[++index] : std::string{};
	post_message = --quantity > 0 ? extra_info_to_read[++index] : std::string{};
	additional_message = --quantity > 0 ? extra_info_to_read[++index] : std::string{};
}

Coordinates InteractableEntity::GetPosition() const {
	return Entity::GetPosition();
}

RenderingSet InteractableEntity::GetRenderingSet() const {
	return RenderingSet{ Sprite{sprite_image, sf::Sprite{}}, GetPosition(), SpriteType::interactable_sprite, GetPosition().z };
}

void InteractableEntity::Update() {}

void InteractableEntity::Interact() {
	if (activation_message.size() > 0 && GetQuest(quest_index).CheckStatus(objects_to_refer_to[1]) && !is_activated) {
		if (additional_message.size() > 0 && GetQuest(quest_index).CheckStatus(objects_to_refer_to[3])) {
			is_activated = true;
			Text::GetInst().SetText(additional_message);
			GetQuest(quest_index).SetStatus(true, objects_to_refer_to[0]);
			return;
		}
		else if (additional_message.size() > 0) {
			Text::GetInst().SetText(activation_message);
			return;
		}
		is_activated = true;
		Text::GetInst().SetText(activation_message);
		GetQuest(quest_index).SetStatus(true, objects_to_refer_to[0]);
	}
	else if (post_message.size() > 0 && is_activated) Text::GetInst().SetText(post_message);
	else {
		Text::GetInst().SetText(default_message);
		if (objects_to_refer_to[1].compare("none") == 0) GetQuest(quest_index).SetStatus(true, objects_to_refer_to[0]);
		GetQuest(quest_index).SetStatus(true, objects_to_refer_to[2]);
	}
}

SerialInteractableEntity::SerialInteractableEntity(const ObjectInfo& info, Level* level_ref) : Entity(info, level_ref) {
	Deserialize(info.extra_info);
	for (std::size_t index = 0; index < current_position.size(); index++) {
		level_ref->SetInteractableObject(this, current_position[index]);
	}
}

void SerialInteractableEntity::Deserialize(const std::vector<std::string>& extra_info_to_read) {
	is_activated = false;
	std::size_t index = 1;
	quest_index = std::stoll(extra_info_to_read[index]);
	self_index = std::stoll(extra_info_to_read[++index]);
	int quantity = std::stoll(extra_info_to_read[++index]);
	default_message = extra_info_to_read[++index];
	activation_message = --quantity > 0 ? extra_info_to_read[++index] : std::string{};
	post_message = --quantity > 0 ? extra_info_to_read[++index] : std::string{};
	additional_message = --quantity > 0 ? extra_info_to_read[++index] : std::string{};
}

Coordinates SerialInteractableEntity::GetPosition() const {
	return Entity::GetPosition();
}

RenderingSet SerialInteractableEntity::GetRenderingSet() const {
	return RenderingSet{ Sprite{sprite_image, sf::Sprite{}}, GetPosition(), SpriteType::interactable_sprite, GetPosition().z };
}

void SerialInteractableEntity::Update() {}

void SerialInteractableEntity::Interact() {}

DoublePressActivationEntity::DoublePressActivationEntity(const ObjectInfo& info, Level* level_ref) : SerialInteractableEntity(info, level_ref) {}

Coordinates DoublePressActivationEntity::GetPosition() const {
	return SerialInteractableEntity::GetPosition();
}

RenderingSet DoublePressActivationEntity::GetRenderingSet() const {
	return RenderingSet{ Sprite{sprite_image, sf::Sprite{}}, GetPosition(), SpriteType::interactable_sprite, GetPosition().z };
}

void DoublePressActivationEntity::Update() {}

void DoublePressActivationEntity::Interact() {
	if (default_message.compare(Text::GetInst().GetCurrentMessageIndex()) == 0) {
		Text::GetInst().SetText(activation_message);
		is_activated = true;
		GetQuest(quest_index).SetStatus(self_index);
	}
	else if (is_activated) Text::GetInst().SetText(post_message);
	else Text::GetInst().SetText(default_message);
}

void DoublePressActivationEntity::Deserialize(const std::vector<std::string>& extra_info_to_read) {
	SerialInteractableEntity::Deserialize(extra_info_to_read);
}

SinglePressActivationEntity::SinglePressActivationEntity(const ObjectInfo& info, Level* level_ref) : SerialInteractableEntity(info, level_ref) {}

Coordinates SinglePressActivationEntity::GetPosition() const {
	return SerialInteractableEntity::GetPosition();
}

RenderingSet SinglePressActivationEntity::GetRenderingSet() const {
	return RenderingSet{ Sprite{sprite_image, sf::Sprite{}}, GetPosition(), SpriteType::interactable_sprite, GetPosition().z };
}

void SinglePressActivationEntity::Update() {}

void SinglePressActivationEntity::Interact() {
	Text::GetInst().SetText(default_message);
	if (is_activated) return;
	is_activated = true;
	GetQuest(quest_index).SetStatus(self_index);
}

void SinglePressActivationEntity::Deserialize(const std::vector<std::string>& extra_info_to_read) {
	SerialInteractableEntity::Deserialize(extra_info_to_read);
}

Door::Door(const ObjectInfo& info, Level* level_ref) : Entity(info, level_ref) {
	Deserialize(info.extra_info);
	for (std::size_t index = 0; index < current_position.size(); index++) {
		level_ref->SetInteractableObject(this, current_position[index]);
	}
}

void Door::Deserialize(const std::vector<std::string>& extra_info_to_read) {
	std::size_t index = 1;
	level_name = extra_info_to_read[index];
	is_locked = std::stoi(extra_info_to_read[++index]);
	if (!is_locked) {
		quest_index = 0;
		return;
	}
	quest_index = std::stoll(extra_info_to_read[++index]);
	int quantity = std::stoll(extra_info_to_read[++index]);
	default_message = extra_info_to_read[++index];
	activation_message = --quantity > 0 ? extra_info_to_read[++index] : std::string{};
	post_message = --quantity > 0 ? extra_info_to_read[++index] : std::string{};
	additional_message = --quantity > 0 ? extra_info_to_read[++index] : std::string{};
}

Coordinates Door::GetPosition() const {
	return Entity::GetPosition();
}

RenderingSet Door::GetRenderingSet() const {
	return RenderingSet{ Sprite{sprite_image, sf::Sprite{}}, GetPosition(), SpriteType::interactable_sprite, GetPosition().z };
}

void Door::Update() {}

void Door::Interact() {
	if (is_locked) {
		if (GetQuest(quest_index).CheckStatus() || GetQuest(quest_index).CheckStatus("done")) {
			is_locked = false;
			if (activation_message.size() > 0) Text::GetInst().SetText(activation_message);
		}
		else {
			Text::GetInst().SetText(default_message);
			return;
		}
	}
	if (level_name.compare("end") == 0) {
		LevelSwitcher::GetInst().FinishGame();
		return;
	}
	LevelSwitcher::GetInst().SetLevel(level_name);
}

Readable::Readable(const ObjectInfo& info, Level* level_ref) : Entity(info, level_ref) {
	Deserialize(info.extra_info);
	for (std::size_t index = 0; index < current_position.size(); index++) {
		level_ref->SetInteractableObject(this, current_position[index]);
	}
}

void Readable::Deserialize(const std::vector<std::string>& extra_info_to_read) {
	std::size_t index = 1;
	default_message = extra_info_to_read[index];
}

Coordinates Readable::GetPosition() const {
	return Entity::GetPosition();
}

RenderingSet Readable::GetRenderingSet() const {
	return RenderingSet{ Sprite{sprite_image, sf::Sprite{}}, GetPosition(), SpriteType::interactable_sprite, GetPosition().z };
}

void Readable::Update() {}

void Readable::Interact() {
	Text::GetInst().SetText(default_message);
}
