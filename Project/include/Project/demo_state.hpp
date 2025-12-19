#ifndef PROJECT_DEMOSTATE_HPP_
#define PROJECT_DEMOSTATE_HPP_

#include "Iridium/application_window.hpp"
#include "Iridium/sub_window.hpp"
#include "Iridium/vector.hpp"
#include "Iridium/dev_utils.hpp"
#include "Iridium/random.hpp"

#include "Iridium/rendering/shapes.hpp"

#include "Iridium/input/mouse.hpp"

#include "Iridium/state_machine.hpp"
#include "Iridium/state.hpp"

class TestState;

IRIDIUM_STATE_CLASS(DemoState)
public:
	Ir::Render::Rectangle r;
	std::unique_ptr<sf::Text> textArea;

	std::unique_ptr<sf::Font> font;

	void OnInitialize() override {
		r.SetSize(20.f, 20.f);
		r.SetPosition(Ir::Vector{30.f, 30.f});
		r.SetAnchor(10.f, 10.f);
		r.SetColor(sf::Color::Red);
	}

	void OnUpdate() override {
		r.SetSize(r.GetSize() + Ir::Vector(.25f, .5f));
		r.SetAngle(r.GetAngle() + 1.f);

		if (Ir::MouseInput::IsPressed(sf::Mouse::Button::Right))
			this->LoadState<TestState>();
	}
	
	void OnReceiveEvent(const sf::Event& _e) override { std::cout << _e.is<sf::Event::KeyPressed>(); }

	void OnRender(Ir::ApplicationWindow& _window) override {
		_window.Render(r);
	}
		
	void OnEnd() override {}
};

#endif // PROJECT_DEMOSTATE_HPP_