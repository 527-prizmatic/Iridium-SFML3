#include <iostream>
#include <chrono>

#include "Iridium/application_window.hpp"
#include "Iridium/vector.hpp"
#include "Iridium/dev_utils.hpp"
#include "Iridium/random.hpp"
#include "Iridium/rendering/shapes.hpp"

int main() {
	std::cout << '\a';

	sf::CircleShape c;
	c.setRadius(25.f);
	c.setFillColor(sf::Color::Green);
	c.setPosition(sf::Vector2f{25.f, 25.f});

	Ir::Render::Rectangle r;
	r.SetSize(20.f, 20.f);
	r.SetPosition(Ir::Vector{30.f, 30.f});
	r.SetAnchor(10.f, 10.f);
	r.SetColor(sf::Color::Red);

	Ir::ApplicationWindow window{Ir::Vector{ 800.f, 600.f }};
	window.SetFPS(60u);
	while (1) {
		window.Clear(sf::Color{200, 200, 200});
		r.SetSize(r.GetSize() + Ir::Vector(.25f, .5f));
		window.Render(c);
		window.Render(r);
		window.Flush();
	}
}