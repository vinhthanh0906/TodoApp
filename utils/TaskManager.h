#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <vector>
#include <string>
#include "Task.h"
#include "FileManager.h"

class TaskManager {
private:
    std::vector<Task> tasks;
    int nextId;
    FileManager fileManager;
    
public:
    // Constructor
    TaskManager(const std::string& filename = "tasks.dat");
    
    // Destructor
    ~TaskManager();
    
    // Task operations
    void addTask(const std::string& title, const std::string& desc, 
                 const std::string& category, const std::string& dateTime, 
                 int priority = 2);
    
    void deleteTask(int id);
    
    bool editTask(int id, int editChoice, const std::string& newValue);
    
    bool markTaskComplete(int id);
    
    Task* findTask(int id);
    
    // Getters
    const std::vector<Task>& getTasks() const { return tasks; }
    std::vector<Task>& getTasksRef() { return tasks; }
    
    // File operations
    void save();
    void load();
};

#endif // TASKMANAGER_H