#include "GameStarter.h"
#include "MyEntities.h"
#include "FileReader.h"

int main(int argc, char** argv) {
	if (argc != 2) return 0;
	FileReader::SetDirectory(argv[1]);
	std::unordered_map<char, std::function<WorldObject* (ObjectInfo, Level*)>> constructors = {
		{'D', [](ObjectInfo obj, Level* level_ref) { return new Door{ obj, level_ref }; }},
		{'O', [](ObjectInfo obj, Level* level_ref) { return new InteractableEntity{ obj, level_ref }; }},
		{'R', [](ObjectInfo obj, Level* level_ref) { return new Readable{ obj, level_ref }; }},
		{'S', [](ObjectInfo obj, Level* level_ref) { return new SinglePressActivationEntity{ obj, level_ref }; }},
        {'T', [](ObjectInfo obj, Level* level_ref) { return new DoublePressActivationEntity{ obj, level_ref }; }}
	};
    std::string start_level { "Levels/1f_corridor.txt" };
	std::string player_sprite_name {"Sprites/final/player.png"};
    StartGame(1024, 800, std::string{"Tiny Quest"}, constructors, start_level, player_sprite_name);
    return 0;
}