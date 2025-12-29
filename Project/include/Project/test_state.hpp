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
	Ir::SubWindow sub{Ir::Vector{200.f, 200.f}};
	Ir::Render::Quad spr;

	std::unique_ptr<sf::Texture> skull;

	void OnInitialize() override {
		c.SetRadius(25.f);
		c.SetPosition(Ir::Vector{70.f, 70.f});
		c.SetAnchor(10.f, 10.f);
		c.SetColor(sf::Color::Blue);
		c.SetVertexCount(6u);

		sub.SetPosition(Ir::Vector{100.f, 100.f});
		sub.SetRenderFrameColor(sf::Color(128,128,255,128));

		skull = std::make_unique<sf::Texture>("../resources/appears.png");
		spr.SetTexture(*skull);
		spr.SetPosition(Ir::Vector{10.f, 10.f});
	}

	void OnUpdate(Ir::ApplicationWindow& _window) override {
		c.SetAngle(c.GetAngle() + 1.0_rad);

		if (Ir::MouseInput::IsPressed(sf::Mouse::Button::Right))
			this->LoadState<DemoState>();
		
		// Placeholder so that GCC does not trigger compilation errors from unused window parameters
		_window.SetTitle(_window.GetTitle());
	}
	
	void OnReceiveEvent(const sf::Event& _e) override {
		if (auto scroll = _e.getIf<sf::Event::MouseWheelScrolled>()) {
			sub.SetSize(sub.GetSize() + Ir::Vector{scroll->delta, -scroll->delta});
		}
		std::cout << _e.is<sf::Event::KeyPressed>();
	}

	void OnRender(Ir::ApplicationWindow& _window) override {
		sub.Clear(sf::Color(32,32,32));

		Ir::Vector pos = Ir::MouseInput::GetPosition();
		if (Ir::MouseInput::IsActive(sf::Mouse::Button::Left))
			pos += Ir::Vector(100.f, 100.f);
		sub.SetPosition(pos);
		
		sub.Render(c);
		_window.Render(spr);
		_window.Render(sub);
	}
		
	void OnEnd() override {}
};

#endif // PROJECT_TESTSTATE_HPP_