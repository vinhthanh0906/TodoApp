#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cmath>

using namespace std;

// Convert "YYYY-MM-DD HH:MM" to time_t
time_t parseTime(const string& datetime) {
    tm t = {};
    istringstream ss(datetime);
    ss >> get_time(&t, "%Y-%m-%d %H:%M");
    t.tm_sec = 0;
    return mktime(&t);
}

// Calculate difference and format it nicely
void showTimeDifference(const string& scheduledStr) {
    time_t now = time(nullptr);
    time_t scheduled = parseTime(scheduledStr);

    double diff = difftime(scheduled, now); // seconds
    bool isPast = diff < 0;
    diff = fabs(diff);

    int totalMinutes = static_cast<int>(diff / 60);
    int days = totalMinutes / (24 * 60);
    int hours = (totalMinutes % (24 * 60)) / 60;
    int minutes = totalMinutes % 60;

    cout << fixed << setprecision(0);
    cout << "Current time:  " << put_time(localtime(&now), "%Y-%m-%d %H:%M") << endl;
    cout << "Scheduled for: " << scheduledStr << endl;
    cout << "→ ";

    if (days >= 1)
        cout << days << " day(s) " << hours << " hour(s)";
    else if (hours >= 1)
        cout << hours << " hour(s) " << minutes << " minute(s)";
    else
        cout << minutes << " minute(s)";

    cout << (isPast ? " ago" : " remaining") << endl;
}

int main() {
    string scheduledTime;
    cout << "Enter scheduled time (YYYY-MM-DD HH:MM): ";
    getline(cin, scheduledTime);

    showTimeDifference(scheduledTime);
    return 0;
}
