#include "GameStarter.h"

void StartGame(int window_length, int window_width, const std::string& window_name, std::unordered_map<char, std::function<WorldObject* (ObjectInfo, Level*)>> constructors,
	const std::string& start_level_name, const std::string& player_sprite) {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(window_length, window_width), window_name, sf::Style::Default, settings);
	Renderer renderer{ window };
	InputManager input_manager;
	LevelFactory level_factory{ constructors, input_manager, player_sprite };
	LevelSwitcher::GetInst().SetLevel(start_level_name);
	while (window.isOpen()) {
		if (LevelSwitcher::GetInst().IsGameFinished()) window.close();
		level_factory.Update(LevelSwitcher::GetInst().GetLevel());
		renderer.GetNewRenderBunch(CreateRenderingSet(level_factory.GetLevelObjects(LevelSwitcher::GetInst().GetLevel())));
		renderer.Display();
		input_manager.ProccessInput();
	}
}