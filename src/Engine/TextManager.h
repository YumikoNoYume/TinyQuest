#pragma once

#include "Utilities.h"
#include "FileReader.h"

class Text {
public:
	static Text& GetInst();
	void SetText(const std::string& text_to_set);
	RenderingSet GetRenderingSet() const;
	std::string GetCurrentMessageIndex() const;
	void SetFont(const std::string& font_to_set);
	void SetPosition(Coordinates position_to_set);
	void SetSize(std::size_t size_to_set);
	void SetColor(sf::Color color_to_set);
private:
	Text();
	sf::Font font;
	std::string text;
	Coordinates position;
	std::unordered_map<std::string, std::string> messages;
	std::string current_message;
	std::size_t text_size;
	sf::Color text_color;
};