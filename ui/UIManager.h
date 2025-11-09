#ifndef UIMANAGER_H
#define UIMANAGER_H

#include <string>
#include <vector>
#include "utils/Task.h"

class UIManager {
private:
    void clearScreen();
    
public:
    // Display methods
    void printHeader();
    void showMenu();
    void displayTasks(const std::vector<Task>& tasks, bool detailed = false);
    
    // Alert display
    void displayUpcomingAlert(const Task& task, int minutesRemaining);
    void displayEventTimeAlert(const Task& task);
    
    // User input prompts
    void showEditMenu();
    void showSuccessMessage(const std::string& message);
    void showErrorMessage(const std::string& message);
    void showInfoMessage(const std::string& message);
    
    // Utility
    void waitForEnter();
    void pauseFor(int seconds);
};

#endif // UIMANAGER_H