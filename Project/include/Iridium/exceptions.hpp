#ifndef IRIDIUM_HPP_EXCEPTIONS_HPP_
#define IRIDIUM_HPP_EXCEPTIONS_HPP_

namespace Ir {
	namespace Exceptions {
		class InvalidRenderTarget : public std::exception {
		public:
			const char * what() { return "Attempted to use invalid render target"; }
		};
	}
}

#endif // IRIDIUM_HPP_EXCEPTIONS_HPP_