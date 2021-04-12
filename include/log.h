#pragma once

#include <atomic>
#include <string>
#include <ostream>
#include <vector>
#include <mutex>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <map>
#include <sstream>
#include <utility>
#include <thread>

#define pf_log(level, message) pathfinder::Logger::Get().log(level, message, __FILE__, __LINE__)
#define pf_log_info(message) pathfinder::Logger::Get().info(message, __FILE__, __LINE__)

#ifdef _MSC_VER
#define pf_log_trace(message) pathfinder::Logger::Get().trace(message, __FILE__, __LINE__, __FUNCSIG__)
#define pf_log_debug(message) pathfinder::Logger::Get().debug(message, __FILE__, __LINE__, __FUNCSIG__)
#define pf_log_warning(message) pathfinder::Logger::Get().trace(message, __FILE__, __LINE__, __FUNCSIG__)
#define pf_log_error(message) pathfinder::Logger::Get().error(message, __FILE__, __LINE__, __FUNCSIG__)
#elif __GNUC__
#define pf_log_trace(message) pathfinder::Logger::Get().trace(message, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define pf_log_debug(message) pathfinder::Logger::Get().debug(message, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define pf_log_warning(message) pathfinder::Logger::Get().trace(message, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#define pf_log_error(message) pathfinder::Logger::Get().error(message, __FILE__, __LINE__, __PRETTY_FUNCTION__)
#elif
#define pf_log_trace(message) pathfinder::Logger::Get().trace(message, __FILE__, __LINE__, __func__)
#define pf_log_debug(message) pathfinder::Logger::Get().debug(message, __FILE__, __LINE__, __func__)
#define pf_log_warning(message) pathfinder::Logger::Get().trace(message, __FILE__, __LINE__, __func__)
#define pf_log_error(message) pathfinder::Logger::Get().error(message, __FILE__, __LINE__, __func__)
#endif

namespace pathfinder {

	enum class LogLevel : size_t
	{
		TRACE = 0,
		DEBUG = 1,
		INFO = 2,
		WARNING = 3,
		ERROR = 4,
	};

	class Logger
	{
	public:
		static Logger& Get();

		Logger(Logger const&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator=(Logger const&) = delete;
		Logger& operator=(Logger&&) = delete;

		Logger& showThreadId(bool use);
		Logger& addStream(std::ostream& os, LogLevel level = LogLevel::INFO);

		using strp_t = const char *;
		using str_t = const std::string&;
		using adcquire_lock = std::unique_lock<std::mutex>;

		void log(LogLevel level, str_t message, strp_t file = nullptr, int line = -1, strp_t function = nullptr);
		void trace(str_t message, strp_t file = nullptr, int line = -1, strp_t function = nullptr);
		void debug(str_t message, strp_t file = nullptr, int line = -1, strp_t function = nullptr);
		void info(str_t message, strp_t file = nullptr, int line = -1);
		void warning(str_t message, strp_t file = nullptr, int line = -1, strp_t function = nullptr);
		void error(str_t message, strp_t file = nullptr, int line = -1, strp_t function = nullptr);

	private:
		Logger();
		~Logger() = default;

		using leveled_stream = std::pair<LogLevel, std::reference_wrapper<std::ostream>>;

		void log(
			leveled_stream& stream,
			str_t timestamp,
			LogLevel level,
			str_t message,
			strp_t file = nullptr,
			int line = -1,
			strp_t function = nullptr);

		std::string now();
		std::string stripPath(str_t path);

		std::vector<leveled_stream> m_streams;
		std::mutex m_mutex;
		bool m_showThreadId;
	};

}