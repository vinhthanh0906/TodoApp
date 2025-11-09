#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "Task.h"

class FileManager {
private:
    std::string dataFile;
    
public:
    // Constructor
    FileManager(const std::string& filename = "tasks.dat");
    
    // Save tasks to file
    void saveTasks(const std::vector<Task>& tasks);
    
    // Load tasks from file
    std::vector<Task> loadTasks(int& nextId);
    
    // Get data file path
    std::string getDataFile() const { return dataFile; }
    void setDataFile(const std::string& filename) { dataFile = filename; }
};

#endif // FILEMANAGER_H