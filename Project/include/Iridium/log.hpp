#ifndef IRIDIUM_LOG_HPP_
#define IRIDIUM_LOG_HPP_

/// Comment out to disable logging
 #define IRIDIUM_ENABLE_LOGGING

#ifdef IRIDIUM_ENABLE_LOGGING
	#define LOG_INFO(msg) ir::log::info(msg)
	#define LOG_WARN(msg) ir::log::warn(msg)
	#define LOG_ERROR(msg) ir::log::error(msg)
#else
	#define LOG_INFO(msg) ((void)0)
	#define LOG_WARN(msg) ((void)0)
	#define LOG_ERROR(msg) ((void)0)
#endif // IRIDIUM_ENABLE_LOGGING

#include <string_view>

namespace ir::log {
	void startSession();

	void info(std::string_view msg);
	void warn(std::string_view msg);
	void error(std::string_view msg);

	void endSession();
}

#endif // IRIDIUM_LOG_HPP_