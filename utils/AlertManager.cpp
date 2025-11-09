#include "AlertManager.h"
#include "TimeUtility.h"
#include <ctime>
#include <thread>
#include <chrono>

AlertManager::AlertManager(UIManager& ui) : uiManager(ui) {}

void AlertManager::checkAlerts(std::vector<Task>& tasks) {
    time_t now = time(0);
    
    for (auto& task : tasks) {
        if (task.getHasAlert() && !task.getIsCompleted()) {
            // Alert if event is within 5 minutes
            double diff = TimeUtility::getTimeDifference(task.getScheduledTime(), now);
            
            if (diff > 0 && diff <= 300) { // 5 minutes = 300 seconds
                int minutesRemaining = (int)(diff / 60);
                uiManager.displayUpcomingAlert(task, minutesRemaining);
            }
            // Alert if event time has arrived
            else if (diff <= 0 && diff >= -60) { // Just passed, within 1 minute
                uiManager.displayEventTimeAlert(task);
                task.setHasAlert(false); // Disable alert after showing
            }
        }
    }
}

void AlertManager::startAlertMonitor(std::vector<Task>& tasks) {
    while (true) {
        checkAlerts(tasks);
        std::this_thread::sleep_for(std::chrono::seconds(30)); // Check every 30 seconds
    }
}