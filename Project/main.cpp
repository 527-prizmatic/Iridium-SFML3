#include "Iridium/application_window.hpp"
#include "Iridium/sub_window.hpp"
#include "Iridium/vector.hpp"
#include "Iridium/dev_utils.hpp"
#include "Iridium/random.hpp"

#include "Iridium/rendering/shapes.hpp"

#include "Iridium/input/mouse.hpp"

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

	Ir::SubWindow sub{Ir::Vector{100.f, 200.f}};
	sub.SetPosition(Ir::Vector{100.f, 100.f});

	Ir::ApplicationWindow window{Ir::Vector{1280.f, 720.f}};
	window.SetFPS(60u);
	Ir::MouseInput::Setup(window);

	while (1) {
		Ir::MouseInput::Update();

		r.SetSize(r.GetSize() + Ir::Vector(.25f, .5f));
		r.SetAngle(r.GetAngle() + 1.f);
		c.SetAngle(c.GetAngle() + 1.f);

		window.Clear(sf::Color{64, 64, 64});
		sub.Clear(sf::Color::Black);

		Ir::Vector pos = Ir::MouseInput::GetPosition();
		if (Ir::MouseInput::IsActive(sf::Mouse::Button::Left))
			pos += Ir::Vector(100.f, 100.f);
		sub.SetPosition(pos);
		
		window.Render(r);
		sub.Render(c);
		window.Render(sub);
		window.Flush();
	}
}