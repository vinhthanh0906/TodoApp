#include "TimeUtility.h"
#include <sstream>
#include <iomanip>

std::string TimeUtility::getCurrentTimeString() {
    time_t now = time(0);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return std::string(buffer);
}

std::string TimeUtility::timeToString(time_t t) {
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", localtime(&t));
    return std::string(buffer);
}

time_t TimeUtility::stringToTime(const std::string& dateStr) {
    struct tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
    return mktime(&tm);
}

double TimeUtility::getTimeDifference(time_t future, time_t past) {
    return difftime(future, past);
}


/* Countdown pseudo code 
- Take a current time asd



*/