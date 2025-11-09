#include "Task.h"

Task::Task(int _id, std::string _title, std::string _desc, std::string _cat, 
           time_t _time, int _priority) {
    id = _id;
    title = _title;
    description = _desc;
    category = _cat;
    scheduledTime = _time;
    isCompleted = false;
    hasAlert = true;
    priority = _priority;
}