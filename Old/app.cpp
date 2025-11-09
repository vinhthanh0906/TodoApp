#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <thread>
#include <chrono>
#include <fstream>

using namespace std;

// ANSI color codes
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";
const string BOLD = "\033[1m";
const string BG_RED = "\033[41m";
const string BG_GREEN = "\033[42m";
const string BG_YELLOW = "\033[43m";

// Event/Task structure
struct Task {
    int id;
    string title;
    string description;
    string category;
    time_t scheduledTime;
    bool isCompleted;
    bool hasAlert;
    int priority; // 1=Low, 2=Medium, 3=High
    
    Task(int _id, string _title, string _desc, string _cat, time_t _time, int _priority = 2) {
        id = _id;
        title = _title;
        description = _desc;
        category = _cat;
        scheduledTime = _time;
        isCompleted = false;
        hasAlert = true;
        priority = _priority;
    }
};

class TodoApp {
private:
    vector<Task> tasks;
    int nextId;
    string dataFile;
    
    void clearScreen() {
        cout << "\033[2J\033[1;1H";
    }
    
    string getCurrentTimeString() {
        time_t now = time(0);
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&now));
        return string(buffer);
    }
    
    string timeToString(time_t t) {
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M", localtime(&t));
        return string(buffer);
    }
    
    time_t stringToTime(string dateStr) {
        struct tm tm = {};
        istringstream ss(dateStr);
        ss >> get_time(&tm, "%Y-%m-%d %H:%M");
        return mktime(&tm);
    }
    
    string getPriorityString(int priority) {
        if (priority == 3) return RED + "HIGH" + RESET;
        else if (priority == 2) return YELLOW + "MEDIUM" + RESET;
        else return GREEN + "LOW" + RESET;
    }
    
    string getCategoryColor(string category) {
        if (category == "work") return BLUE;
        else if (category == "personal") return GREEN;
        else if (category == "health") return RED;
        else if (category == "study") return MAGENTA;
        else return CYAN;
    }
    
    void printHeader() {
        cout << BOLD << CYAN << "╔═══════════════════════════════════════════════════════════════════════════╗" << RESET << endl;
        cout << BOLD << CYAN << "║" << RESET << "                    " << BOLD << MAGENTA << "📋 TODO & EVENT MANAGER 📋" << RESET << "                        " << BOLD << CYAN << "║" << RESET << endl;
        cout << BOLD << CYAN << "╠═══════════════════════════════════════════════════════════════════════════╣" << RESET << endl;
        cout << BOLD << CYAN << "║ " << RESET << "Current Time: " << BOLD << WHITE << getCurrentTimeString() << RESET;
        cout << "                                            " << BOLD << CYAN << "║" << RESET << endl;
        cout << BOLD << CYAN << "╚═══════════════════════════════════════════════════════════════════════════╝" << RESET << endl;
        cout << endl;
    }
    
    void saveToFile() {
        ofstream file(dataFile);
        if (file.is_open()) {
            for (const auto& task : tasks) {
                file << task.id << "|"
                     << task.title << "|"
                     << task.description << "|"
                     << task.category << "|"
                     << task.scheduledTime << "|"
                     << task.isCompleted << "|"
                     << task.hasAlert << "|"
                     << task.priority << endl;
            }
            file.close();
        }
    }
    
    void loadFromFile() {
        ifstream file(dataFile);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                istringstream ss(line);
                string token;
                vector<string> tokens;
                
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
                    task.isCompleted = stoi(tokens[5]);
                    task.hasAlert = stoi(tokens[6]);
                    tasks.push_back(task);
                    
                    if (task.id >= nextId) {
                        nextId = task.id + 1;
                    }
                }
            }
            file.close();
        }
    }

public:
    TodoApp(string filename = "tasks.dat") {
        dataFile = filename;
        nextId = 1;
        loadFromFile();
    }
    
    ~TodoApp() {
        saveToFile();
    }
    
    void addTask(string title, string desc, string category, string dateTime, int priority = 2) {
        time_t scheduledTime = stringToTime(dateTime);
        Task newTask(nextId++, title, desc, category, scheduledTime, priority);
        tasks.push_back(newTask);
        saveToFile();
        
        cout << GREEN << "✓ Task added successfully! (ID: " << newTask.id << ")" << RESET << endl;
    }
    
    void deleteTask(int id) {
        auto it = remove_if(tasks.begin(), tasks.end(), [id](const Task& t) {
            return t.id == id;
        });
        
        if (it != tasks.end()) {
            tasks.erase(it, tasks.end());
            saveToFile();
            cout << GREEN << "✓ Task deleted successfully!" << RESET << endl;
        } else {
            cout << RED << "✗ Task not found!" << RESET << endl;
        }
    }
    
    void changeTask(int id) {
        auto it = find_if(tasks.begin(), tasks.end(), [id](const Task& t) {
            return t.id == id;
        });
        
        if (it != tasks.end()) {
            cout << CYAN << "Editing Task ID: " << id << RESET << endl;
            cout << "Current: " << it->title << endl << endl;
            
            cout << "1. Change Title" << endl;
            cout << "2. Change Description" << endl;
            cout << "3. Change Category" << endl;
            cout << "4. Change Date/Time" << endl;
            cout << "5. Change Priority" << endl;
            cout << "6. Toggle Completion" << endl;
            cout << "7. Toggle Alert" << endl;
            cout << "0. Back" << endl;
            cout << "\nChoice: ";
            
            int choice;
            cin >> choice;
            cin.ignore();
            
            switch(choice) {
                case 1: {
                    cout << "New title: ";
                    getline(cin, it->title);
                    break;
                }
                case 2: {
                    cout << "New description: ";
                    getline(cin, it->description);
                    break;
                }
                case 3: {
                    cout << "New category (work/personal/health/study/other): ";
                    getline(cin, it->category);
                    break;
                }
                case 4: {
                    cout << "New date/time (YYYY-MM-DD HH:MM): ";
                    string datetime;
                    getline(cin, datetime);
                    it->scheduledTime = stringToTime(datetime);
                    break;
                }
                case 5: {
                    cout << "New priority (1=Low, 2=Medium, 3=High): ";
                    cin >> it->priority;
                    break;
                }
                case 6: {
                    it->isCompleted = !it->isCompleted;
                    cout << (it->isCompleted ? GREEN + "✓ Marked as completed" : YELLOW + "○ Marked as incomplete") << RESET << endl;
                    break;
                }
                case 7: {
                    it->hasAlert = !it->hasAlert;
                    cout << (it->hasAlert ? GREEN + "🔔 Alert enabled" : "🔕 Alert disabled") << RESET << endl;
                    break;
                }
            }
            
            saveToFile();
            cout << GREEN << "✓ Task updated successfully!" << RESET << endl;
        } else {
            cout << RED << "✗ Task not found!" << RESET << endl;
        }
    }
    
    void displayTasks(bool showAll = true) {
        clearScreen();
        printHeader();
        
        if (tasks.empty()) {
            cout << YELLOW << "📭 No tasks yet! Add your first task." << RESET << endl;
            return;
        }
        
        // Sort by time
        vector<Task> sortedTasks = tasks;
        sort(sortedTasks.begin(), sortedTasks.end(), [](const Task& a, const Task& b) {
            return a.scheduledTime < b.scheduledTime;
        });
        
        cout << BOLD << "╔════╦════════════════════════════════╦═════════════════════╦════════════╦════════════╦═══════════╗" << RESET << endl;
        cout << BOLD << "║ ID ║ Title                          ║ Scheduled           ║ Category   ║ Priority   ║ Status    ║" << RESET << endl;
        cout << BOLD << "╠════╬════════════════════════════════╬═════════════════════╬════════════╬════════════╬═══════════╣" << RESET << endl;
        
        time_t now = time(0);
        
        for (const auto& task : sortedTasks) {
            if (!showAll && task.isCompleted) continue;
            
            string status;
            if (task.isCompleted) {
                status = GREEN + "✓ Done" + RESET;
            } else if (task.scheduledTime < now) {
                status = RED + "⚠ Overdue" + RESET;
            } else {
                status = YELLOW + "○ Pending" + RESET;
            }
            
            string title = task.title;
            if (title.length() > 22) title = title.substr(0, 19) + "...";
            
            string categoryColor = getCategoryColor(task.category);
            
            cout << "║ " << setw(2) << task.id << " ║ ";
            cout << left << setw(22) << title << "         ║ ";
            cout << timeToString(task.scheduledTime) << "    ║ ";
            cout << categoryColor << setw(8) << task.category << RESET << "   ║ ";
            cout << setw(8) << getPriorityString(task.priority) << "     ║";
            cout << setw(6) << status << "  ║" << endl;
            
            if (!task.description.empty()) {
                cout << "║    ║ " << CYAN << task.description.substr(0, 65) << RESET;
                cout << string(max(0, 65 - (int)task.description.length()), ' ') << " ║" << endl;
            }
            
                cout << "╠════╬════════════════════════════════╬═════════════════════╬════════════╬════════════╬═══════════╣" << endl;
        }
        cout << BOLD << "╚════╩════════════════════════════════╩═════════════════════╩════════════╩════════════╩═══════════╝" << RESET << endl;
        cout << endl;
    }
    
    void checkAlerts() {
        time_t now = time(0);
        
        for (auto& task : tasks) {
            if (task.hasAlert && !task.isCompleted) {
                // Alert if event is within 5 minutes
                double diff = difftime(task.scheduledTime, now);
                
                if (diff > 0 && diff <= 300) { // 5 minutes = 300 seconds
                    cout << "\a"; // Beep sound
                    cout << BG_YELLOW << BOLD << RED << "🔔 ALERT! EVENT COMING SOON!" << RESET << endl;
                    cout << BOLD << "Event: " << RESET << task.title << endl;
                    cout << BOLD << "Time: " << RESET << timeToString(task.scheduledTime) << endl;
                    cout << BOLD << "In: " << RESET << (int)(diff / 60) << " minutes" << endl;
                    cout << string(60, '=') << endl;
                }
                // Alert if event time has arrived
                else if (diff <= 0 && diff >= -60) { // Just passed, within 1 minute
                    cout << "\a";
                    cout << BG_RED << BOLD << WHITE << "⏰ EVENT TIME!" << RESET << endl;
                    cout << BOLD << "Event: " << RESET << task.title << endl;
                    cout << BOLD << "Scheduled: " << RESET << timeToString(task.scheduledTime) << endl;
                    cout << string(60, '=') << endl;
                    
                    task.hasAlert = false; // Disable alert after showing
                    saveToFile();
                }
            }
        }
    }
    
    void showMenu() {
        cout << BOLD << CYAN << "┌─────────────────────────────────────┐" << RESET << endl;
        cout << BOLD << CYAN << "│" << RESET << "           " << BOLD << WHITE << "MAIN MENU" << RESET << "              " << BOLD << CYAN << "   │" << RESET << endl;
        cout << BOLD << CYAN << "├─────────────────────────────────────┤" << RESET << endl;
        cout << BOLD << CYAN << "│" << RESET << "  1. " << GREEN << "Add Task/Event" << RESET << "           " << BOLD << CYAN << "       │" << RESET << endl;
        cout << BOLD << CYAN << "│" << RESET << "  2. " << YELLOW << "View All Tasks" << RESET << "           " << BOLD << CYAN << "       │" << RESET << endl;
        cout << BOLD << CYAN << "│" << RESET << "  3. " << BLUE << "Edit Task" << RESET << "                " << BOLD << CYAN << "       │" << RESET << endl;
        cout << BOLD << CYAN << "│" << RESET << "  4. " << RED << "Delete Task" << RESET << "              " << BOLD << CYAN << "       │" << RESET << endl;
        cout << BOLD << CYAN << "│" << RESET << "  5. " << MAGENTA << "Mark as Complete" << RESET << "         " << BOLD << CYAN << "       │" << RESET << endl;
        cout << BOLD << CYAN << "│" << RESET << "  6. " << CYAN << "Check Alerts" << RESET << "             " << BOLD << CYAN << "       │" << RESET << endl;
        cout << BOLD << CYAN << "│" << RESET << "  0. " << WHITE << "Exit" << RESET << "                     " << BOLD << CYAN << "       │" << RESET << endl;
        cout << BOLD << CYAN << "└─────────────────────────────────────┘" << RESET << endl;
        cout << "\nChoice: ";
    }
    
    void run() {
        bool running = true;
        
        while (running) {
            displayTasks();
            checkAlerts();
            showMenu();
            
            int choice;
            cin >> choice;
            cin.ignore();
            
            switch(choice) {
                case 1: {
                    cout << BOLD << GREEN << "\n➕ ADD NEW TASK/EVENT" << RESET << endl;
                    cout << string(40, 'o') << endl;
                    
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
                    
                    addTask(title, desc, category, datetime, priority);
                    
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                }
                case 2: {
                    displayTasks(true);
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                }
                case 3: {
                    cout << "Enter Task ID to edit: ";
                    int id;
                    cin >> id;
                    cin.ignore();
                    changeTask(id);
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                }
                case 4: {
                    cout << "Enter Task ID to delete: ";
                    int id;
                    cin >> id;
                    cin.ignore();
                    
                    cout << RED << "Are you sure? (y/n): " << RESET;
                    char confirm;
                    cin >> confirm;
                    cin.ignore();
                    
                    if (confirm == 'y' || confirm == 'Y') {
                        deleteTask(id);
                    }
                    
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                }
                case 5: {
                    cout << "Enter Task ID to mark as complete: ";
                    int id;
                    cin >> id;
                    cin.ignore();
                    
                    auto it = find_if(tasks.begin(), tasks.end(), [id](const Task& t) {
                        return t.id == id;
                    });
                    
                    if (it != tasks.end()) {
                        it->isCompleted = true;
                        saveToFile();
                        cout << GREEN << "✓ Task marked as completed!" << RESET << endl;
                    } else {
                        cout << RED << "✗ Task not found!" << RESET << endl;
                    }
                    
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                }
                case 6: {
                    cout << BOLD << CYAN << "\n🔔 Checking for alerts..." << RESET << endl;
                    checkAlerts();
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                }
                case 0: {
                    running = false;
                    cout << BOLD << GREEN << "\n👋 Goodbye! Your tasks have been saved." << RESET << endl;
                    break;
                }
                default: {
                    cout << RED << "Invalid choice! Please try again." << RESET << endl;
                    this_thread::sleep_for(chrono::seconds(1));
                    break;
                }
            }
        }
    }
    
    // Background alert monitor (can be run in separate thread)
    void startAlertMonitor() {
        while (true) {
            checkAlerts();
            this_thread::sleep_for(chrono::seconds(30)); // Check every 30 seconds
        }
    }
};

int main() {
    cout << BOLD << MAGENTA << "═══════════════════════════════════════════════════════" << RESET << endl;
    cout << BOLD << CYAN << "       Welcome to TODO & Event Manager!" << RESET << endl;
    cout << BOLD << MAGENTA << "═══════════════════════════════════════════════════════" << RESET << endl;
    cout << endl;
    
    this_thread::sleep_for(chrono::seconds(1));
    
    TodoApp app("my_tasks.dat");
    
    // Optional: Start background alert monitor in separate thread
    // thread alertThread(&TodoApp::startAlertMonitor, &app);
    // alertThread.detach();
    
    app.run();
    
    return 0;
}