#include <iostream>
#include <chrono>

#include "Iridium/application_window.hpp"
#include "Iridium/vector.hpp"
#include "Iridium/dev_utils.hpp"
#include "Iridium/random.hpp"
#include "Iridium/rendering/shapes.hpp"

int main() {
	std::cout << '\a';

	Ir::Render::Rectangle r;
	r.SetSize(20.f, 20.f);
	r.SetPosition(Ir::Vector{30.f, 30.f});
	r.SetAnchor(10.f, 10.f);
	r.SetColor(sf::Color::Red);

	Ir::Render::Circle c;
	c.SetRadius(25.f);
	c.SetPosition(Ir::Vector{70.f, 70.f});
	c.SetAnchor(10.f, 10.f);
	c.SetColor(sf::Color::Blue);
	c.SetVertexCount(6u);

	Ir::ApplicationWindow window{Ir::Vector{ 800.f, 600.f }};
	window.SetFPS(60u);
	while (1) {
		window.Clear(sf::Color{200, 200, 200});
		r.SetSize(r.GetSize() + Ir::Vector(.25f, .5f));
		r.SetAngle(r.GetAngle() + 1.f);
		c.SetAngle(c.GetAngle() + 1.f);
		window.Render(r);
		window.Render(c);
		window.Flush();
	}
}