#include "logger.h"
#include <gtest/gtest.h>

TEST(TEST_LOGGER, TEST_LOGGER_INFOMATIONS) {
    LOG_INFO("%s", "test for LOG_INFO");
    LOG_ERROR("%s", "test for LOG_ERROR");
    LOG_FATAL("%s", "test for LOG_FATAL");
    LOG_DEBUG("%s", "test for LOG_DEBUG");
}