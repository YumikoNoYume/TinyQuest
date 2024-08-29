#include "QuestManager.h"

Quest1& Quest1::GetInst() {
	static Quest1 quest;
	return quest;
}

bool Quest1::CheckStatus(const std::string& object_to_check) const {
	return false;
}

bool Quest1::CheckStatus() const {
	return is_door_opened;
}

void Quest1::SetStatus(bool status_to_set, const std::string& object_to_set) {}

void Quest1::SetStatus(std::size_t index_to_set) {
	sequence.push_back(index_to_set);
	if (sequence.size() < 6) return;
	if (std::is_sorted(sequence.begin(), sequence.end())) {
		is_door_opened = true;
		Text::GetInst().SetText("Text/q1ss.txt");
	}
	else {
		sequence.clear();
		Text::GetInst().SetText("Text/q1sf.txt");
	}
}

Quest2& Quest2::GetInst() {
	static Quest2 quest;
	return quest;
}

bool Quest2::CheckStatus(const std::string& object_to_check) const {
	return steps.find(object_to_check)->second;
}

bool Quest2::CheckStatus() const {
	return false;
}

void Quest2::SetStatus(bool status_to_set, const std::string& object_to_set) {
	if (object_to_set.compare("none") == 0) return;
	steps.find(object_to_set)->second = status_to_set;
}

void Quest2::SetStatus(std::size_t index_to_set) {}

Quest2::Quest2() {
	steps = { {"bucket", false}, {"water", false}, {"key", false}, {"piece", false}, {"notes", false}, {"done", false}, {"none", false} };
}


Quest3& Quest3::GetInst() {
	static Quest3 quest;
	return quest; 
}

bool Quest3::CheckStatus(const std::string& object_to_check) const {
	return steps.find(object_to_check)->second;
}

bool Quest3::CheckStatus() const {
	return false;
}

void Quest3::SetStatus(bool status_to_set, const std::string& object_to_set) {
	if (object_to_set.compare("none") == 0) return;
	steps.find(object_to_set)->second = status_to_set;
}

void Quest3::SetStatus(std::size_t index_to_set) {}

Quest3::Quest3() {
	steps = {{"recipe", false}, {"potion", false}, {"dagger", false}, {"done", false}, {"none", false} };
}

Quest4& Quest4::GetInst() {
	static Quest4 quest;
	return quest;
}

bool Quest4::CheckStatus(const std::string& object_to_check) const {
	return false;
}

bool Quest4::CheckStatus() const {
	return is_door_opened;
}

void Quest4::SetStatus(std::size_t index_to_set) {
	sequence.push_back(index_to_set);
	if (sequence.size() == 8) {
		is_door_opened = true;
		Text::GetInst().SetText("Text/q4sc.txt");
	}
}

void Quest4::SetStatus(bool status_to_set, const std::string& object_to_set) {}

Quest& GetQuest(std::size_t quest_to_get) {
	switch (quest_to_get) {
	case 1: return Quest1::GetInst();
	case 2: return Quest2::GetInst();
	case 3: return Quest3::GetInst();
	case 4: return Quest4::GetInst();
	}
}