#include "Renderer.h"

std::vector<RenderingSet> CreateRenderingSet(const std::vector<WorldObject*>& objects_to_render) {
	std::vector<RenderingSet> render_bunch{};
	for (std::size_t index = 0; index < objects_to_render.size(); index++) {
		render_bunch.push_back(objects_to_render[index]->GetRenderingSet());
	}
	return render_bunch;
}

Renderer::Renderer(sf::RenderWindow& window) : window(window) {}

Renderer::Renderer(const std::vector<RenderingSet>& render_bunch, sf::RenderWindow& window) : window(window){
	GetNewRenderBunch(render_bunch);
}

void Renderer::GetNewRenderBunch(const std::vector<RenderingSet>& bunch_to_render) {
	render_bunch = bunch_to_render;
	render_bunch.push_back(Text::GetInst().GetRenderingSet());
	ComputeWindowSetCoordinates();
	std::sort(render_bunch.begin(), render_bunch.end(), [](RenderingSet set1, RenderingSet set2) { return set1.coordinates.y < set2.coordinates.y; });
}

void Renderer::Display() {
	window.clear(sf::Color::Black);
	for (std::size_t index = 0; index < render_bunch.size(); index++) {
		if (render_bunch[index].sprite_type == SpriteType::text) {
			render_bunch[index].message.message.setFont(render_bunch[index].message.font);
			render_bunch[index].message.message.setString(render_bunch[index].message.text);
			render_bunch[index].message.message.setCharacterSize(render_bunch[index].message.size);
			render_bunch[index].message.message.setColor(render_bunch[index].message.color);
			window.draw(render_bunch[index].message.message);
		}
		else {
			render_bunch[index].sprite.sprite.setTexture(render_bunch[index].sprite.texture);
			window.draw(render_bunch[index].sprite.sprite);
		}
	}
	window.display();
}

void Renderer::ComputeWindowSetCoordinates() {
	for (std::size_t index = 0; index < render_bunch.size(); index++) {
		if (render_bunch[index].sprite_type == SpriteType::level_sprite) continue;
		render_bunch[index].coordinates.x = render_bunch[index].coordinates.x * 44 + 16 - 44;
		if (render_bunch[index].sprite_type == SpriteType::player_sprite) {
			render_bunch[index].coordinates.y = render_bunch[index].coordinates.y * 22 + 116 - (22 * render_bunch[index].sprite_height + 13);
		}
		else {
			render_bunch[index].coordinates.y = render_bunch[index].coordinates.y * 22 + 116 - (22 * render_bunch[index].sprite_height);
		}
		if (render_bunch[index].sprite_type == SpriteType::text) {
			render_bunch[index].message.message.setPosition(render_bunch[index].coordinates.x, 500);
		}
		else render_bunch[index].sprite.sprite.setPosition(render_bunch[index].coordinates.x, render_bunch[index].coordinates.y);
	}
}
