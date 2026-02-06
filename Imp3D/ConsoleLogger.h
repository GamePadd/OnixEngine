#pragma once
#include <string>
#include <ctime>
#include <iostream>

namespace Imp {
	enum class LOG {ERROR, INFO};
	
	class ConsoleLogger {
		private:
			ConsoleLogger() = default;
			~ConsoleLogger() = default;

			ConsoleLogger(const ConsoleLogger&) = delete;
			ConsoleLogger& operator= (const ConsoleLogger&) = delete;

		public:
			static ConsoleLogger& Instance();

			void Log(const std::string& str, LOG);
	};
}