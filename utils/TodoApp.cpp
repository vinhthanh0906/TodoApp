#include "TodoApp.h"
#include "ui/ColorTheme.h"
#include <iostream>

using namespace std;

TodoApp::TodoApp(const string& filename) 
    : taskManager(filename), alertManager(uiManager) {
}

void TodoApp::handleAddTask() {
    cout << ColorTheme::BOLD << ColorTheme::GREEN << "\n➕ ADD NEW TASK/EVENT" << ColorTheme::RESET << endl;
    cout << string(40, '=') << endl;
    
    cout << "Title: ";
    string title;
    getline(cin, title);
    
    cout << "Description: ";
    string desc;
    getline(cin, desc);
    
    cout << "Category (work/personal/health/study/other): ";
    string category;
    getline(cin, category);
    
    cout << "Date and Time (YYYY-MM-DD HH:MM): ";
    string datetime;
    getline(cin, datetime);
    
    cout << "Priority (1=Low, 2=Medium, 3=High): ";
    int priority;
    cin >> priority;
    cin.ignore();
    
    taskManager.addTask(title, desc, category, datetime, priority);
    
    uiManager.showSuccessMessage("Task added successfully!");
    uiManager.waitForEnter();
}

void TodoApp::handleViewTasks() {
    uiManager.displayTasks(taskManager.getTasks(), true);
    uiManager.waitForEnter();
}

void TodoApp::handleEditTask() {
    cout << "Enter Task ID to edit: ";
    int id;
    cin >> id;
    cin.ignore();
    
    Task* task = taskManager.findTask(id);
    if (task == nullptr) {
        uiManager.showErrorMessage("Task not found!");
        uiManager.waitForEnter();
        return;
    }
    
    cout << ColorTheme::CYAN << "Editing Task ID: " << id << ColorTheme::RESET << endl;
    cout << "Current: " << task->getTitle() << endl << endl;
    
    uiManager.showEditMenu();
    
    int choice;
    cin >> choice;
    cin.ignore();
    
    if (choice == 0) return;
    
    string newValue;
    
    switch(choice) {
        case 1:
            cout << "New Title: ";
            getline(cin, newValue);
            break;
        case 2:
            cout << "New Description: ";
            getline(cin, newValue);
            break;
        case 3:
            cout << "New Category: ";
            getline(cin, newValue);
            break;
        case 4:
            cout << "New Date/Time (YYYY-MM-DD HH:MM): ";
            getline(cin, newValue);
            break;
        case 5:
            cout << "New Priority (1=Low, 2=Medium, 3=High): ";
            getline(cin, newValue);
            break;
        case 6:
        case 7:
            newValue = ""; // Toggle operations don't need input
            break;
        default:
            uiManager.showErrorMessage("Invalid choice!");
            uiManager.waitForEnter();
            return;
    }
    
    if (taskManager.editTask(id, choice, newValue)) {
        uiManager.showSuccessMessage("Task updated successfully!");
    } else {
        uiManager.showErrorMessage("Failed to update task!");
    }
    
    uiManager.waitForEnter();
}

void TodoApp::handleDeleteTask() {
    cout << "Enter Task ID to delete: ";
    int id;
    cin >> id;
    cin.ignore();
    
    cout << ColorTheme::RED << "Are you sure? (y/n): " << ColorTheme::RESET;
    char confirm;
    cin >> confirm;
    cin.ignore();
    
    if (confirm == 'y' || confirm == 'Y') {
        taskManager.deleteTask(id);
        uiManager.showSuccessMessage("Task deleted successfully!");
    }
    
    uiManager.waitForEnter();
}

void TodoApp::handleMarkComplete() {
    cout << "Enter Task ID to mark as complete: ";
    int id;
    cin >> id;
    cin.ignore();
    
    if (taskManager.markTaskComplete(id)) {
        uiManager.showSuccessMessage("Task marked as completed!");
    } else {
        uiManager.showErrorMessage("Task not found!");
    }
    
    uiManager.waitForEnter();
}

void TodoApp::handleCheckAlerts() {
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "\nChecking for alerts..." << ColorTheme::RESET << endl;
    alertManager.checkAlerts(taskManager.getTasksRef());
    uiManager.waitForEnter();
}

void TodoApp::run() {
    bool running = true;
    
    while (running) {
        uiManager.displayTasks(taskManager.getTasks());
        alertManager.checkAlerts(taskManager.getTasksRef());
        uiManager.showMenu();
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                handleAddTask();
                break;
            case 2:
                handleViewTasks();
                break;
            case 3:
                handleEditTask();
                break;
            case 4:
                handleDeleteTask();
                break;
            case 5:
                handleMarkComplete();
                break;
            case 6:
                handleCheckAlerts();
                break;
            case 0:
                running = false;
                cout << ColorTheme::BOLD << ColorTheme::GREEN << "\n Goodbye! Your tasks have been saved." << ColorTheme::RESET << endl;
                break;
            default:
                uiManager.showErrorMessage("Invalid choice! Please try again.");
                uiManager.pauseFor(1);
                break;
        }
    }
}