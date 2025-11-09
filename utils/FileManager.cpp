#include "FileManager.h"
#include <fstream>
#include <sstream>

FileManager::FileManager(const std::string& filename) {
    dataFile = filename;
}

void FileManager::saveTasks(const std::vector<Task>& tasks) {
    std::ofstream file(dataFile);
    if (file.is_open()) {
        for (const auto& task : tasks) {
            file << task.getId() << "|"
                 << task.getTitle() << "|"
                 << task.getDescription() << "|"
                 << task.getCategory() << "|"
                 << task.getScheduledTime() << "|"
                 << task.getIsCompleted() << "|"
                 << task.getHasAlert() << "|"
                 << task.getPriority() << std::endl;
        }
        file.close();
    }
}

std::vector<Task> FileManager::loadTasks(int& nextId) {
    std::vector<Task> tasks;
    std::ifstream file(dataFile);
    
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::istringstream ss(line);
            std::string token;
            std::vector<std::string> tokens;
            
            while (getline(ss, token, '|')) {
                tokens.push_back(token);
            }
            
            if (tokens.size() >= 8) {
                Task task(
                    stoi(tokens[0]),
                    tokens[1],
                    tokens[2],
                    tokens[3],
                    stoll(tokens[4]),
                    stoi(tokens[7])
                );
                task.setIsCompleted(stoi(tokens[5]));
                task.setHasAlert(stoi(tokens[6]));
                tasks.push_back(task);
                
                if (task.getId() >= nextId) {
                    nextId = task.getId() + 1;
                }
            }
        }
        file.close();
    }
    
    return tasks;
}