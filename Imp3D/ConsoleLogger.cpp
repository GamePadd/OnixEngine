#include "ConsoleLogger.h"

namespace Imp {

	ConsoleLogger& ConsoleLogger::Instance() {
		static ConsoleLogger logger;
		return logger;
	}

	void ConsoleLogger::Log(const std::string& str, LOG type) {
		std::time_t current_time = std::time(NULL);
		std::tm* local_time = std::localtime(&current_time);

		std::string log_type_string = "";
		switch (type) {
			case LOG::ERROR: log_type_string = "ERROR"; break;
			case LOG::INFO: log_type_string = "INFO"; break;
			default: log_type_string = "UNKNOWN_TYPE";
		}
		std::cout << "[" 
					<< local_time->tm_hour << ":"
					<< local_time->tm_min << ":"
					<< local_time->tm_sec
					<< "][" << log_type_string << "] " << str << std::endl;
	}
}