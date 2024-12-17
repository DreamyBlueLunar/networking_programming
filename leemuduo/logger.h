#pragma once

#include <string>

#include "noncopyable.h"

#define LOG_BUF_LEN 1024

// LOG_INFO("%s, %d", arg1, arg2);
#define LOG_INFO(format_msg, ...)  do {                             \
        lee::logger& logger = lee::logger::get_instance();          \
        logger.set_log_level(INFO);                                 \
        char buffer[LOG_BUF_LEN] = {0};                             \
        snprintf(buffer, LOG_BUF_LEN, format_msg, ##__VA__ARGS__);  \
        logger.log(buffer);                                         \
    } while(0)

#define LOG_ERROR(format_msg, ...)  do {                            \
        lee::logger& logger = lee::logger::get_instance();          \
        logger.set_log_level(ERROR);                                \
        char buffer[LOG_BUF_LEN] = {0};                             \
        snprintf(buffer, LOG_BUF_LEN, format_msg, ##__VA__ARGS__);  \
        logger.log(buffer);                                         \
    } while(0)

#define LOG_FATAL(format_msg, ...)  do {                            \
        lee::logger& logger = lee::logger::get_instance();          \
        logger.set_log_level(FATAL);                                \
        char buffer[LOG_BUF_LEN] = {0};                             \
        snprintf(buffer, LOG_BUF_LEN, format_msg, ##__VA__ARGS__);  \
        logger.log(buffer);                                         \
    } while(0)

#ifdef MUDEBUG
#define LOG_DEBUG(format_msg, ...)  do {                            \
        lee::logger& logger = lee::logger::get_instance();          \
        logger.set_log_level(DEBUG);                                \
        char buffer[LOG_BUF_LEN] = {0};                             \
        snprintf(buffer, LOG_BUF_LEN, format_msg, ##__VA__ARGS__);  \
        logger.log(buffer);                                         \
    } while(0)
#else
#define LOG_DEBUG(format_msg, ...)
#endif

enum log_level {
    INFO,
    ERROR,
    FATAL,
    DEBUG
};

namespace lee
{
class logger : noncopyable {
public:
    static logger& get_instance(void);
    void set_log_level(int);
    void log(std::string&);

private:
    logger() = default;
    ~logger() = default;

    int log_level_;
}; 
} // namespace lee
