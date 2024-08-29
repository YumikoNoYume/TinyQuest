#include "InputManager.h"

void InputManager::ProccessInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (last_key == '/' && !is_key_pressed) {
			last_key = 'a';
			is_key_pressed = true;
		}
		else if (last_key == 'a') {
			last_key = '/';
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { 
		if (last_key == '/' && !is_key_pressed) {
			last_key = 'd';
			is_key_pressed = true;
		}
		else if (last_key == 'd') {
			last_key = '/';
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (last_key == '/' && !is_key_pressed) {
			last_key = 's';
			is_key_pressed = true;
		}
		else if (last_key == 's') {
			last_key = '/';
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (last_key == '/' && !is_key_pressed) {
			last_key = 'w';
			is_key_pressed = true;
		}
		else if (last_key == 'w') {
			last_key = '/';
		}
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		if (last_key == '/' && !is_key_pressed) {
			last_key = 'e';
			is_key_pressed = true;
		}
		else if (last_key == 'e') {
			last_key = '/';
		}
	}
	else {
		last_key = '/'; 
		is_key_pressed = false;
	}
}

char InputManager::GetLastKey() const {
	return last_key;
}