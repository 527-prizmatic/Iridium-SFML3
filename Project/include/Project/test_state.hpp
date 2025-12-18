#ifndef PROJECT_TESTSTATE_HPP_
#define PROJECT_TESTSTATE_HPP_

#include "Iridium/application_window.hpp"
#include "Iridium/sub_window.hpp"
#include "Iridium/vector.hpp"
#include "Iridium/dev_utils.hpp"
#include "Iridium/random.hpp"

#include "Iridium/rendering/shapes.hpp"

#include "Iridium/input/mouse.hpp"

#include "Iridium/state_machine.hpp"
#include "Iridium/state.hpp"

class DemoState;

IRIDIUM_STATE_CLASS(TestState)
public:
	Ir::Render::Circle c;
	Ir::SubWindow sub{Ir::Vector{100.f, 200.f}};

	void OnInitialize() override {
		c.SetRadius(25.f);
		c.SetPosition(Ir::Vector{70.f, 70.f});
		c.SetAnchor(10.f, 10.f);
		c.SetColor(sf::Color::Blue);
		c.SetVertexCount(6u);

		sub.SetPosition(Ir::Vector{100.f, 100.f});
	}

	void OnUpdate() override {
		c.SetAngle(c.GetAngle() + 1.f);

		if (Ir::MouseInput::IsPressed(sf::Mouse::Button::Right))
			this->LoadState<DemoState>();
	}
	
	void OnReceiveEvent(const sf::Event& _e) override { std::cout << _e.is<sf::Event::KeyPressed>(); }

	void OnRender(Ir::ApplicationWindow& _window) override {
		sub.Clear(sf::Color::Black);

		Ir::Vector pos = Ir::MouseInput::GetPosition();
		if (Ir::MouseInput::IsActive(sf::Mouse::Button::Left))
			pos += Ir::Vector(100.f, 100.f);
		sub.SetPosition(pos);
		
		sub.Render(c);
		_window.Render(sub);
	}
		
	void OnEnd() override {}
};

#endif // PROJECT_TESTSTATE_HPP_