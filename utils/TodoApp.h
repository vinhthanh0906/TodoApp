#ifndef TODOAPP_H
#define TODOAPP_H

#include "TaskManager.h"
#include "ui/UIManager.h"
#include "AlertManager.h"

class TodoApp {
private:
    TaskManager taskManager;
    UIManager uiManager;
    AlertManager alertManager;
    
    // Handle menu choices
    void handleAddTask();
    void handleViewTasks();
    void handleEditTask();
    void handleDeleteTask();
    void handleMarkComplete();
    void handleCheckAlerts();
    
public:
    // Constructor
    TodoApp(const std::string& filename = "my_tasks.dat");
    
    // Main application loop
    void run();
};

#endif // TODOAPP_H