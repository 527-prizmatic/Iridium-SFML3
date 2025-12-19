#ifndef IRIDIUM_EXCEPTIONS_HPP_
#define IRIDIUM_EXCEPTIONS_HPP_

namespace Ir {
	namespace Exceptions {
		class InvalidRenderTarget : public std::exception {
		public:
			const char * what() { return "Attempted to use invalid render target"; }
		};
		
		class BadResourceID : public std::exception {
		public:
			BadResourceID(std::string _id) : m_badID { _id } {}

			const char * what() { return std::string{ "Requested resource ID \"" + this->m_badID + "\" does not exist" }.c_str(); }

		private:
			std::string m_badID {};
		};
		
		class BadStateID : public std::exception {
		public:
			BadStateID(std::string _id) : m_badID { _id } {}

			const char * what() { return std::string{ "State machine attempted to update nonexistent state \"" + this->m_badID + "\"" }.c_str(); }

		private:
			std::string m_badID {};
		};
	}
}

#endif // IRIDIUM_EXCEPTIONS_HPP_