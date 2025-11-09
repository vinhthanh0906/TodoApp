#ifndef TASK_H
#define TASK_H

#include <string>
#include <ctime>

class Task {
private:
    int id;
    std::string title;
    std::string description;
    std::string category;
    time_t scheduledTime;
    bool isCompleted;
    bool hasAlert;
    int priority; // 1=Low, 2=Medium, 3=High

public:
    // Constructor
    Task(int _id, std::string _title, std::string _desc, std::string _cat, 
         time_t _time, int _priority = 2);
    
    // Getters
    int getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getDescription() const { return description; }
    std::string getCategory() const { return category; }
    time_t getScheduledTime() const { return scheduledTime; }
    bool getIsCompleted() const { return isCompleted; }
    bool getHasAlert() const { return hasAlert; }
    int getPriority() const { return priority; }
    
    // Setters
    void setTitle(const std::string& _title) { title = _title; }
    void setDescription(const std::string& _desc) { description = _desc; }
    void setCategory(const std::string& _cat) { category = _cat; }
    void setScheduledTime(time_t _time) { scheduledTime = _time; }
    void setIsCompleted(bool _completed) { isCompleted = _completed; }
    void setHasAlert(bool _alert) { hasAlert = _alert; }
    void setPriority(int _priority) { priority = _priority; }
    
    // Utility methods
    void toggleCompletion() { isCompleted = !isCompleted; }
    void toggleAlert() { hasAlert = !hasAlert; }
};

#endif // TASK_H