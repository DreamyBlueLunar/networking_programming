#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <string>

#include "noncopyable.h"

class LoggerStream {
public:
    LoggerStream() {}

    ~LoggerStream() {
        std::cout << stream_.str() << std::endl; // 输出日志
    }

    template<typename T>
    LoggerStream& operator<<(const T& msg) {
        stream_ << msg; // 将消息添加到流中
        return *this;
    }

private:
    std::ostringstream stream_;
};

class logger : lee::noncopyable {
public:
    static logger& get_instance() {
        static logger instance;
        return instance;
    }

    void set_log_level(int level) {
        log_level_ = level;
    }

    LoggerStream& get_log_stream(const char* file, int line, const std::string& time, const char* date) {
        // 这里可以根据需要添加文件名、行号、时间等信息
        return loggerstream << "[" << date << " " << time << "][" << file << ":" << line << "] ";
    }

private:
    logger() = default;
    ~logger() = default;

    int log_level_;
    LoggerStream loggerstream;
};

#define LOG_INFO logger::get_instance().get_log_stream(__FILE__, __LINE__, __TIME__, __DATE__)

int main() {
    logger::get_instance().set_log_level(1); // 设置日志级别

    // 连续输出
    LOG_INFO << "This is an info message." 
             << " Additional info: " << 42 
             << " and some more text.";

    return 0;
}
