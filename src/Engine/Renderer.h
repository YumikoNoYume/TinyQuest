#pragma once

#include <initializer_list>
#include <vector>
#include <algorithm>
#include "Entities.h"

std::vector<RenderingSet> CreateRenderingSet(const std::vector<WorldObject*>& objects_to_render);

class Renderer {
public:
	Renderer(sf::RenderWindow&);
	Renderer(const std::vector<RenderingSet>& render_bunch, sf::RenderWindow& window);
	void GetNewRenderBunch(const std::vector<RenderingSet>& bunch_to_render);
	void Display();
private:
	void ComputeWindowSetCoordinates();
	std::vector<RenderingSet> render_bunch;
	sf::RenderWindow& window;
};