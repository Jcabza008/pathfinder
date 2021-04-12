#include "log.h"

namespace pathfinder {

    constexpr char c_ISO8601_time[] = "%H:%M:%S";

    static const std::map<LogLevel, std::string> c_LevelString
    {
        { LogLevel::TRACE, "TRACE" },
        { LogLevel::DEBUG, "DEBUG" },
        { LogLevel::INFO, "INFO" },
        { LogLevel::WARNING, "WARNING" },
        { LogLevel::ERROR, "ERROR" },
    };

    inline std::ostream& operator<<(std::ostream& os, LogLevel level)
    {
        os << c_LevelString.at(level);
        return os;
    }

    Logger& Logger::Get()
    {
        static Logger instance;
        return instance;
    }

    Logger& Logger::showThreadId(bool use)
    {
        adcquire_lock lock(m_mutex);
        m_showThreadId = use;
        return *this;
    }

    Logger& Logger::addStream(std::ostream& os, LogLevel level)
    {
        adcquire_lock lock(m_mutex);
        m_streams.push_back({ level, os });
        return *this;
    }

    void Logger::log(LogLevel level, str_t message, strp_t file, int line, strp_t function)
    {
        auto timestamp = now();
        adcquire_lock lock(m_mutex);
        for (auto& stream : m_streams)
            log(stream, timestamp, level, message, file, line, function);
    }

    void Logger::trace(str_t message, strp_t file, int line, strp_t function)
    {
        log(LogLevel::TRACE, message, file, line, function);
    }

    void Logger::debug(str_t message, strp_t file, int line, strp_t function)
    {
        log(LogLevel::DEBUG, message, file, line, function);
    }

    void Logger::info(str_t message, strp_t file, int line)
    {
        log(LogLevel::INFO, message, file, line);
    }

    void Logger::warning(str_t message, strp_t file, int line, strp_t function)
    {
        log(LogLevel::WARNING, message, file, line, function);
    }

    void Logger::error(str_t message, strp_t file, int line, strp_t function)
    {
        log(LogLevel::ERROR, message, file, line, function);
    }

    Logger::Logger()
    : m_showThreadId(true)
    {
    }

    void Logger::log(
        leveled_stream& stream,
        str_t timestamp,
        LogLevel level,
        str_t message,
        strp_t file,
        int line,
        strp_t function)
    {
        if (level < stream.first)
            return;

        std::ostream& os = stream.second;
        os  << "[" << timestamp << "]"
            << "[" << std::setw(5) << std::left << level << "]"
            << " " << message;

        if (file && line != -1)
            os << " (" << stripPath(file) << ":" << line << ")";

        if (function)
            os << " " << function;

        if (m_showThreadId)
        {
            os << " thread_id:" << std::this_thread::get_id();
        }

        os << std::endl;
    }

    std::string Logger::now()
    {
        using namespace std::chrono;
        char buff[sizeof "HH:mm:ss"];
        auto now = system_clock::now();
        auto tt = system_clock::to_time_t(now);
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

        std::strftime(buff, sizeof(buff), c_ISO8601_time, std::localtime(&tt));
        std::stringstream ss;
        ss << buff << "." << std::setw(3) << std::setfill('0') << ms.count();
        return ss.str();
    }

    std::string Logger::stripPath(str_t path)
    {
        auto cut = path.find_last_of("\\/") + 1;
        return path.substr(cut);
    }

}