#include "UIManager.h"
#include "ColorTheme.h"
#include "utils/TimeUtility.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;

void UIManager::clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void UIManager::printHeader() {
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "╔════════════════════════════════════════════════════════╗" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "║" << ColorTheme::RESET << "                    " << ColorTheme::BOLD << ColorTheme::MAGENTA << "Log System" << ColorTheme::RESET << "     " << ColorTheme::BOLD << ColorTheme::CYAN << "                     ║" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "╠════════════════════════════════════════════════════════╣" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "║ " << ColorTheme::RESET << "Current Time: " << ColorTheme::BOLD << ColorTheme::WHITE << TimeUtility::getCurrentTimeString() << ColorTheme::RESET;
    cout << "                                          " << ColorTheme::BOLD  << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "╚════════════════════════════════════════════════════════╝" << ColorTheme::RESET << endl;
    cout << endl;
}

void UIManager::showMenu() {
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "┌─────────────────────────────────────┐" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "│" << ColorTheme::RESET << "           " << ColorTheme::BOLD << ColorTheme::WHITE << "MAIN MENU" << ColorTheme::RESET << "              " << ColorTheme::BOLD << ColorTheme::CYAN << "   │" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "├─────────────────────────────────────┤" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "│" << ColorTheme::RESET << "  1. " << ColorTheme::GREEN << "Add Task/Event" << ColorTheme::RESET << "           " << ColorTheme::BOLD << ColorTheme::CYAN << "       │" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "│" << ColorTheme::RESET << "  2. " << ColorTheme::YELLOW << "View All Tasks" << ColorTheme::RESET << "           " << ColorTheme::BOLD << ColorTheme::CYAN << "       │" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "│" << ColorTheme::RESET << "  3. " << ColorTheme::BLUE << "Edit Task" << ColorTheme::RESET << "                " << ColorTheme::BOLD << ColorTheme::CYAN << "       │" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "│" << ColorTheme::RESET << "  4. " << ColorTheme::RED << "Delete Task" << ColorTheme::RESET << "              " << ColorTheme::BOLD << ColorTheme::CYAN << "       │" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "│" << ColorTheme::RESET << "  5. " << ColorTheme::MAGENTA << "Mark as Complete" << ColorTheme::RESET << "         " << ColorTheme::BOLD << ColorTheme::CYAN << "       │" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "│" << ColorTheme::RESET << "  6. " << ColorTheme::CYAN << "Check Alerts" << ColorTheme::RESET << "             " << ColorTheme::BOLD << ColorTheme::CYAN << "       │" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "│" << ColorTheme::RESET << "  0. " << ColorTheme::WHITE << "Exit" << ColorTheme::RESET << "                     " << ColorTheme::BOLD << ColorTheme::CYAN << "       │" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "└─────────────────────────────────────┘" << ColorTheme::RESET << endl;
    cout << "\nChoice: ";
}

void UIManager::displayTasks(const vector<Task>& tasks, bool detailed) {
    clearScreen();
    printHeader();
    
    if (tasks.empty()) {
        cout << ColorTheme::YELLOW << "No tasks available. Add a task to get started!" << ColorTheme::RESET << endl;
        return;
    }
    
    cout << ColorTheme::BOLD << "╔════╦════════════════════════════════╦═════════════════════╦════════════╦════════════╦═══════════╗" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << "║ ID ║ TITLE                          ║ SCHEDULED TIME      ║ CATEGORY   ║ PRIORITY   ║ STATUS    ║" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << "╠════╬════════════════════════════════╬═════════════════════╬════════════╬════════════╬═══════════╣" << ColorTheme::RESET << endl;
    
    for (const auto& task : tasks) {
        string status = task.getIsCompleted() ? ColorTheme::GREEN + "✓ Done   " + ColorTheme::RESET : ColorTheme::YELLOW + "  Todo   " + ColorTheme::RESET;
        string categoryColor = ColorTheme::getCategoryColor(task.getCategory());
        
        cout << "║ " << setw(2) << task.getId() << " ║ ";
        cout << setw(30) << left << task.getTitle().substr(0, 30) << " ║ ";
        cout << TimeUtility::timeToString(task.getScheduledTime()) << "    ║ ";
        cout << categoryColor << setw(10) << task.getCategory().substr(0, 10) << ColorTheme::RESET << " ║ ";
        cout << setw(8) << ColorTheme::getPriorityString(task.getPriority()) << "     ║";
        cout << setw(6) << status << "  ║" << endl;
        
        if (!task.getDescription().empty()) {
            cout << "║    ║ " << ColorTheme::CYAN << task.getDescription().substr(0, 65) << ColorTheme::RESET;
            cout << string(max(0, 65 - (int)task.getDescription().length()), ' ') << " ║" << endl;
        }
        
                        cout << "╠════╬════════════════════════════════╬═════════════════════╬════════════╬════════════╬═══════════╣" << endl;
    }
    cout << ColorTheme::BOLD << "╚════╩════════════════════════════════╩═════════════════════╩════════════╩════════════╩═══════════╝" << ColorTheme::RESET << endl;
    cout << endl;
}

void UIManager::displayUpcomingAlert(const Task& task, int minutesRemaining) {
    cout << "\a"; // Beep sound
    cout << ColorTheme::BG_YELLOW << ColorTheme::BOLD << ColorTheme::RED << "ALERT! EVENT COMING SOON!" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << "Event: " << ColorTheme::RESET << task.getTitle() << endl;
    cout << ColorTheme::BOLD << "Time: " << ColorTheme::RESET << TimeUtility::timeToString(task.getScheduledTime()) << endl;
    cout << ColorTheme::BOLD << "In: " << ColorTheme::RESET << minutesRemaining << " minutes" << endl;
    cout << string(60, '=') << endl;
}

void UIManager::displayEventTimeAlert(const Task& task) {
    cout << "\a";
    cout << ColorTheme::BG_RED << ColorTheme::BOLD << ColorTheme::WHITE << "EVENT TIME!" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << "Event: " << ColorTheme::RESET << task.getTitle() << endl;
    cout << ColorTheme::BOLD << "Scheduled: " << ColorTheme::RESET << TimeUtility::timeToString(task.getScheduledTime()) << endl;
    cout << string(60, '=') << endl;
}

void UIManager::showEditMenu() {
    cout << "1. Change Title" << endl;
    cout << "2. Change Description" << endl;
    cout << "3. Change Category" << endl;
    cout << "4. Change Date/Time" << endl;
    cout << "5. Change Priority" << endl;
    cout << "6. Toggle Completion" << endl;
    cout << "7. Toggle Alert" << endl;
    cout << "0. Back" << endl;
    cout << "\nChoice: ";
}

void UIManager::showSuccessMessage(const string& message) {
    cout << ColorTheme::GREEN << "✓ " << message << ColorTheme::RESET << endl;
}

void UIManager::showErrorMessage(const string& message) {
    cout << ColorTheme::RED << "✗ " << message << ColorTheme::RESET << endl;
}

void UIManager::showInfoMessage(const string& message) {
    cout << ColorTheme::CYAN << message << ColorTheme::RESET << endl;
}

void UIManager::waitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

void UIManager::pauseFor(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
}