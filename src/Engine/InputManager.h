#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class InputManager {
public:
	InputManager() = default;
	void ProccessInput();
	char GetLastKey() const;
private:
	char last_key;
	bool is_key_pressed = false;
};
