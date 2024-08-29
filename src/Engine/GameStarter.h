#pragma once

#include "Renderer.h"
#include "FileReader.h"
#include "Entities.h"
#include "LevelFactory.h"
#include "InputManager.h"

void StartGame(int window_length, int window_width, const std::string& window_name, std::unordered_map<char, std::function<WorldObject* (ObjectInfo, Level*)>> constructors, const std::string& start_level_name, const std::string& player_sprite);