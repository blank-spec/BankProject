#pragma once
#include <iomanip>
#include <chrono>
#include <sstream>
#include <ctime>
#include <string>

using namespace std;

// Class to get current time
class Time {
public:
    string getTime() {
        auto now = chrono::system_clock::now();
        time_t nowTime = chrono::system_clock::to_time_t(now);

        tm nowTm;
        localtime_s(&nowTm, &nowTime);

        ostringstream oss;
        oss << put_time(&nowTm, "%Y-%m-%d %H:%M");
        return oss.str();
    }
};