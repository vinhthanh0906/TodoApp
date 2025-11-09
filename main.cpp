#include "utils/TodoApp.h"
#include "ui/ColorTheme.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int main() {
    cout << ColorTheme::BOLD << ColorTheme::MAGENTA << "═══════════════════════════════════════════════════════" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "    Log System online, Welcome back sir!" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::MAGENTA << "═══════════════════════════════════════════════════════" << ColorTheme::RESET << endl;
    cout << endl;
    
    this_thread::sleep_for(chrono::seconds(1));
    
    TodoApp app("my_tasks.dat");
    
    // Optional: Start background alert monitor in separate thread
    // thread alertThread(&TodoApp::startAlertMonitor, &app);
    // alertThread.detach();
    
    app.run();
    
    return 0;
}