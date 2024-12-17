#include "logger.h"
#include <gtest/gtest.h>

#define MUDEBUG

TEST(TEST_LOGGER, TEST_LOGGER_WITH_EXPLICIT_STRING) {
    LOG_INFO("%s", "test for LOG_INFO");
    LOG_ERROR("%s", "test for LOG_ERROR");
    LOG_FATAL("%s", "test for LOG_FATAL");
    LOG_DEBUG("%s", "test for LOG_DEBUG");
}

TEST(TEST_LOGGER, TEST_LOGGER_WITH_CHAR_PTR) {
    char* msg_info = (char*)"test for LOG_INFO";
    char* msg_error = (char*)"test for LOG_ERROR";
    char* msg_fatal = (char*)"test for LOG_FATAL";
    char* msg_debug = (char*)"test for LOG_DEBUG";

    LOG_INFO("%s", msg_info);
    LOG_INFO("%s", msg_error);
    LOG_INFO("%s", msg_fatal);
    LOG_INFO("%s", msg_debug);
}

TEST(TEST_LOGGER, TEST_LOGGER_WITH_STR) {
    std::string msg_info = "test for LOG_INFO";
    std::string msg_error = "test for LOG_ERROR";
    std::string msg_fatal = "test for LOG_FATAL";
    std::string msg_debug = "test for LOG_DEBUG";

    LOG_INFO("%s", msg_info.c_str());
    LOG_INFO("%s", msg_error.c_str());
    LOG_INFO("%s", msg_fatal.c_str());
    LOG_INFO("%s", msg_debug.c_str());
}