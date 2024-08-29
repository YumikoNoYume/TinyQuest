#include "TextManager.h"

Text& Text::GetInst() {
	static Text t;
	return t;
}

void Text::SetText(const std::string& text_to_set) {
	if (messages.find(text_to_set) == messages.end()) {
		std::string file_name{text_to_set};
		messages.insert({ text_to_set, FileReader::ReadTextFile(file_name) });
	}
	text = messages.find(text_to_set)->second;
	current_message = text_to_set;
}

RenderingSet Text::GetRenderingSet() const {
	return RenderingSet{ Sprite{}, position, SpriteType::text, 1, Message{font, text, text_size, sf::Text{}, text_color}};
}

std::string Text::GetCurrentMessageIndex() const {
	return current_message;
}

void Text::SetFont(const std::string& font_to_set) {
	font = FileReader::ReadFontFile(font_to_set);
}

void Text::SetPosition(Coordinates position_to_set) {
	position = position_to_set;
}

void Text::SetSize(std::size_t size_to_set) {
	text_size = size_to_set;
}

void Text::SetColor(sf::Color color_to_set) {
	text_color = color_to_set;
}

Text::Text() {
	font = FileReader::ReadFontFile("Monocraft.otf");
	position = { 1, 50 };
	text_size = 18;
	text_color = sf::Color::White;
}
