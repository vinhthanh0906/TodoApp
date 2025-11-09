#include "TaskManager.h"
#include "TimeUtility.h"
#include <algorithm>

TaskManager::TaskManager(const std::string& filename) : fileManager(filename) {
    nextId = 1;
    load();
}

TaskManager::~TaskManager() {
    save();
}

void TaskManager::addTask(const std::string& title, const std::string& desc, 
                          const std::string& category, const std::string& dateTime, 
                          int priority) {
    time_t scheduledTime = TimeUtility::stringToTime(dateTime);
    Task newTask(nextId++, title, desc, category, scheduledTime, priority);
    tasks.push_back(newTask);
    save();
}

void TaskManager::deleteTask(int id) {
    auto it = std::remove_if(tasks.begin(), tasks.end(), [id](const Task& t) {
        return t.getId() == id;
    });
    
    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        save();
    }
}

bool TaskManager::editTask(int id, int editChoice, const std::string& newValue) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& t) {
        return t.getId() == id;
    });
    
    if (it == tasks.end()) {
        return false;
    }
    
    switch(editChoice) {
        case 1:
            it->setTitle(newValue);
            break;
        case 2:
            it->setDescription(newValue);
            break;
        case 3:
            it->setCategory(newValue);
            break;
        case 4:
            it->setScheduledTime(TimeUtility::stringToTime(newValue));
            break;
        case 5:
            it->setPriority(std::stoi(newValue));
            break;
        case 6:
            it->toggleCompletion();
            break;
        case 7:
            it->toggleAlert();
            break;
        default:
            return false;
    }
    
    save();
    return true;
}

bool TaskManager::markTaskComplete(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& t) {
        return t.getId() == id;
    });
    
    if (it != tasks.end()) {
        it->setIsCompleted(true);
        save();
        return true;
    }
    return false;
}

Task* TaskManager::findTask(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [id](const Task& t) {
        return t.getId() == id;
    });
    
    if (it != tasks.end()) {
        return &(*it);
    }
    return nullptr;
}

void TaskManager::save() {
    fileManager.saveTasks(tasks);
}

void TaskManager::load() {
    tasks = fileManager.loadTasks(nextId);
}