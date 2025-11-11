#include "Countdown.h"
#include <sstream>
#include <iomanip>

std::string Countdown::getRemainingTime(time_t scheduledTime) {
    time_t now = time(0);
    double diff = difftime(scheduledTime, now); // seconds remaining

    if (diff <= 0)
        return "Overdue";

    int totalSeconds = static_cast<int>(diff);
    int days = totalSeconds / 86400;
    totalSeconds %= 86400;
    int hours = totalSeconds / 3600;
    totalSeconds %= 3600;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    std::ostringstream oss;

    if (days > 0)
        oss << days << "d " << hours << "h";
    else if (hours > 0)
        oss << hours << "h " << minutes << "m";
    else if (minutes > 0)
        oss << minutes << "m " << seconds << "s";
    else
        oss << seconds << "s";

    return oss.str();
}
