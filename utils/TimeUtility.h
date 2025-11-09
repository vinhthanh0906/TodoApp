#ifndef TIMEUTILITY_H
#define TIMEUTILITY_H

#include <string>
#include <ctime>

class TimeUtility {
public:
    // Get current time as formatted string
    static std::string getCurrentTimeString();
    
    // Convert time_t to string
    static std::string timeToString(time_t t);
    
    // Convert string to time_t
    static time_t stringToTime(const std::string& dateStr);
    
    // Calculate time difference in seconds
    static double getTimeDifference(time_t future, time_t past);
};

#endif // TIMEUTILITY_H