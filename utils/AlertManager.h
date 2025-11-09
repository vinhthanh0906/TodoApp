#ifndef ALERTMANAGER_H
#define ALERTMANAGER_H

#include <vector>
#include "Task.h"
#include "ui/UIManager.h"

class AlertManager {
private:
    UIManager& uiManager;
    
public:
    // Constructor
    AlertManager(UIManager& ui);
    
    // Check alerts for all tasks
    void checkAlerts(std::vector<Task>& tasks);
    
    // Start background alert monitor (runs in separate thread)
    void startAlertMonitor(std::vector<Task>& tasks);
};

#endif // ALERTMANAGER_H
