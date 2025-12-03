#include <iostream>
#include <gsl/assert>
#include <chrono>

#include "Iridium/application_window.hpp"
#include "Iridium/vector.hpp"
#include "Iridium/dev_utils.hpp"
#include "Iridium/random.hpp"

int main()
{
	// std::cout << "trolfaec" << std::endl;

	// int i = 0;
	// Expects(i == 0);
	// i = 1;
	// Expects(i == 2);
	// std::cout << "good" << std::endl;

	Ir::Vector abc { 3.f, 5.f };
	std::cout << static_cast<std::string>(abc) << std::endl;

	Ir::Benchmark([&](){ abc = abc.ClampMagnitude(1.f, 5.f); }, 1'000'000, "Ir::Vector::ClampMagnitude");
	Ir::Benchmark([&](){ abc = abc.RecToPol(); }, 1'000'000, "Ir::Vector::RecToPol");
	Ir::Benchmark([&](){ abc = abc.PolToRec(); }, 1'000'000, "Ir::Vector::PolToRec");
	Ir::Benchmark([&](){ Ir::Random::Integer32(); }, 1'000'000, "Ir::Random::Integer32");
	Ir::Benchmark([&](){ Ir::Random::DiceRoll("3d6"); }, 1'000'000, "Ir::Random::Integer32");
	
	// for (int i = 0; i < 1000; i++) std::cout << Ir::Random::DiceRoll("bingbngd6[pa]") << "  ";

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