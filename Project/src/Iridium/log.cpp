#include "Iridium/log.hpp"
#include <iostream>
#include <list>
#include <thread>

namespace ir::log {
	namespace {
		struct Entry {
			std::string msg;

			enum class Level : char {
				INFO = 0,
				WARN,
				ERROR
			};
			Level level;
		};
		std::list<Entry> gEntryList;

		std::mutex gMutex;
		std::thread gThread;
		bool gIsRunning { true };

		std::string assembleMessage(Entry& e) {
			std::string str;
			str += "[";
			switch (e.level) {
				case Entry::Level::INFO: str += "INFO"; break;
				case Entry::Level::WARN: str += "WARN"; break;
				case Entry::Level::ERROR: str += "ERROR"; break;
			}
			str += "] ";
			str += e.msg;
			return str;
		}

		void update() {
			while (ir::log::gIsRunning) {
				if (gEntryList.size() != 0) {
					std::lock_guard<std::mutex> lock { ir::log::gMutex };
					std::cout << ir::log::assembleMessage(*ir::log::gEntryList.begin()) << std::endl;
					ir::log::gEntryList.pop_front();
				}
			}
		}

		std::unique_ptr<std::ofstream> file;
	}

	void startSession() {
		ir::log::file = std::make_unique<std::ofstream>("EditorLog.txt");
		if (file && !file->fail()) {
			std::cout.rdbuf(ir::log::file->rdbuf());
		}

		ir::log::gThread = std::thread(ir::log::update);
	}

	void info(std::string_view msg) {
		std::lock_guard<std::mutex> lock { ir::log::gMutex };
		ir::log::gEntryList.push_back({ msg.data(), ir::log::Entry::Level::INFO });
	}

	void warn(std::string_view msg) {
		std::lock_guard<std::mutex> lock { ir::log::gMutex };
		ir::log::gEntryList.push_back({ msg.data(), ir::log::Entry::Level::WARN });
	}

	void error(std::string_view msg) {
		std::lock_guard<std::mutex> lock { ir::log::gMutex };
		ir::log::gEntryList.push_back({ msg.data(), ir::log::Entry::Level::ERROR });
	}

	void endSession() {
		ir::log::gIsRunning = false;
		ir::log::gThread.join();
		ir::log::file->close();
	}
}