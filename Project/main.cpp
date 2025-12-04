#include <iostream>
#include <chrono>

#include "Iridium/application_window.hpp"
#include "Iridium/vector.hpp"
#include "Iridium/dev_utils.hpp"
#include "Iridium/random.hpp"

int main() {
	std::cout << '\a';

	sf::CircleShape c;
	c.setRadius(25.f);
	c.setFillColor(sf::Color::Green);
	c.setPosition(sf::Vector2f{25.f, 25.f});

	Ir::ApplicationWindow window{Ir::Vector{ 800.f, 600.f }};
	while (1) {
		window.Clear(sf::Color{200, 200, 200});
		window.Render(c);
		window.Flush();
	}
}