#pragma once

#include <iostream>
#include <string>

namespace lee {
class time_stamp {
public:
    time_stamp();
    explicit time_stamp(int);

    static time_stamp now();
    std::string to_string() const;

private:
    int64_t microSecondsSinceEpoch_;
};
}