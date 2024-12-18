#include "logger.h"
#include <gtest/gtest.h>

#define MUDEBUG

TEST(TEST_LOGGER, TEST_LOGGER_WITH_EXPLICIT_STRING) {
    LOG_FMT_INFO("%s\n", "test for LOG_FMT_INFO");
    LOG_FMT_ERROR("%s\n", "test for LOG_FMT_ERROR");
    LOG_FMT_FATAL("%s\n", "test for LOG_FMT_FATAL");
    LOG_FMT_DEBUG("%s\n", "test for LOG_FMT_DEBUG");
}

TEST(TEST_LOGGER, TEST_LOGGER_WITH_CHAR_PTR) {
    char* msg_info = (char*)"test for LOG_FMT_INFO";
    char* msg_error = (char*)"test for LOG_FMT_ERROR";
    char* msg_fatal = (char*)"test for LOG_FMT_FATAL";
    char* msg_debug = (char*)"test for LOG_FMT_DEBUG";

    LOG_FMT_INFO("%s\n", msg_info);
    LOG_FMT_ERROR("%s\n", msg_error);
    LOG_FMT_FATAL("%s\n", msg_fatal);
    LOG_FMT_DEBUG("%s\n", msg_debug);
}

TEST(TEST_LOGGER, TEST_LOGGER_WITH_STR) {
    std::string msg_info = "test for LOG_FMT_INFO";
    std::string msg_error = "test for LOG_FMT_ERROR";
    std::string msg_fatal = "test for LOG_FMT_FATAL";
    std::string msg_debug = "test for LOG_FMT_DEBUG";

    LOG_FMT_INFO("%s\n", msg_info.c_str());
    LOG_FMT_ERROR("%s\n", msg_error.c_str());
    LOG_FMT_FATAL("%s\n", msg_fatal.c_str());
    LOG_FMT_DEBUG("%s\n", msg_debug.c_str());
}

TEST(TEST_LOGGER_STREAM, TEST_WITH_EXPLICIT_STR) {
    LOG_INFO << "test for " << "LOG_INFO" << ENDL;
    LOG_ERROR << "test for " << "LOG_INFO" << ENDL;
    LOG_FATAL << "test for " << "LOG_INFO" << ENDL;
    LOG_DEBUG << "test for " << "LOG_INFO" << ENDL;
}

TEST(TEST_LOGGER_STREAM, TEST_WITH_CHAT_PTR) {
    char* msg_info = (char*)"test for LOG_INFO";
    char* msg_error = (char*)"test for LOG_ERROR";
    char* msg_fatal = (char*)"test for LOG_FATAL";
    char* msg_debug = (char*)"test for LOG_DEBUG";

    LOG_INFO << msg_info << ENDL;
    LOG_ERROR << msg_error << ENDL;
    LOG_FATAL << msg_fatal << ENDL;
    LOG_DEBUG << msg_debug << ENDL;
}

TEST(TEST_LOGGER_STREAM, TEST_WITH_STRING) {
    std::string msg_info = "test for LOG_INFO";
    std::string msg_error = "test for LOG_ERROR";
    std::string msg_fatal = "test for LOG_FATAL";
    std::string msg_debug = "test for LOG_DEBUG";

    LOG_INFO << msg_info << ENDL;
    LOG_ERROR << msg_error << ENDL;
    LOG_FATAL << msg_fatal << ENDL;
    LOG_DEBUG << msg_debug << ENDL;
}