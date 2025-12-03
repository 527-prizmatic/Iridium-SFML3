#ifndef IRIDIUM_DEVUTILS_HPP_
#define IRIDIUM_DEVUTILS_HPP_

#include "Iridium/libraries.hpp"

namespace Ir {
	/// @brief Runs a snippet of code a large number of times and prints total execution time to console.
	/// @param _func Function to run
	/// @param _loops Number of times to run the function
	inline void Benchmark(std::function<void(void)> _func, unsigned long _loops = 1'000'000, std::string _test_name = "") {
		std::chrono::steady_clock clock;
		auto startTime = clock.now();

		for (unsigned long a = 0; a < _loops; a++) {
			_func();
		}

		auto endTime = clock.now();
		if (_test_name.compare(""))
			std::cout << "[" << _test_name << "] ";
		std::cout << std::to_string(_loops) << " operations took " << std::to_string((endTime - startTime).count()) << "ns to complete" << std::endl;
	}
}

#endif // IRIDIUM_DEVUTILS_HPP_