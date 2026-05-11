#ifndef IRIDIUM_EXCEPTIONS_HPP_
#define IRIDIUM_EXCEPTIONS_HPP_

namespace ir {
	namespace Exceptions {
		class InvalidRenderTarget : public std::exception {
		public:
			const char * what() { return "Attempted to use invalid render target"; }
		};
		
		class BadResourceID : public std::exception {
		public:
			BadResourceID(std::string id) : badID_ { id } {}

			const char * what() { return std::string{ "Requested resource ID \"" + badID_ + "\" does not exist" }.c_str(); }

		private:
			std::string badID_ {};
		};
		
		class BadStateID : public std::exception {
		public:
			BadStateID(std::string id) : badID_ { id } {}

			const char * what() { return std::string{ "State machine attempted to update nonexistent state \"" + badID_ + "\"" }.c_str(); }

		private:
			std::string badID_ {};
		};
	}
}

#endif // IRIDIUM_EXCEPTIONS_HPP_