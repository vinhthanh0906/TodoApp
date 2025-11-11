#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <string>
#include <ctime>

class Countdown {
public:
    // Returns formatted remaining time: e.g. "2d 4h", "3h 12m", "5m 30s"
    static std::string getRemainingTime(time_t scheduledTime);
};

#endif
