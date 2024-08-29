#include "Utilities.h"

LevelSwitcher& LevelSwitcher::GetInst() {
	static LevelSwitcher switcher;
	return switcher;
}

void LevelSwitcher::SetLevel(const std::string& level_to_set) {
	current_level = level_to_set;
}

std::string LevelSwitcher::GetLevel() const {
	return current_level;
}

bool LevelSwitcher::IsGameFinished() const {
	return is_finished;
}

void LevelSwitcher::FinishGame() {
	is_finished = true;
}