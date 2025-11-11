#include "utils/TodoApp.h"
#include "ui/ColorTheme.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// Loading animation function
void showLoadingAnimation() {
    const int barWidth = 50;
    
    cout << ColorTheme::CYAN << "\n  Loading your tasks..." << ColorTheme::RESET << endl;
    cout << "  [";
    
    for (int i = 0; i <= barWidth; i++) {
        // Calculate percentage
        float progress = (float)i / barWidth;
        int pos = barWidth * progress;
        
        // Clear line and redraw
        cout << "\r  [";
        
        // Draw progress bar
        for (int j = 0; j < barWidth; j++) {
            if (j < pos) {
                cout << ColorTheme::CYAN << "█" << ColorTheme::RESET;
            } else if (j == pos) {
                cout << ColorTheme::YELLOW << "█" << ColorTheme::RESET;
            } else {
                cout << ColorTheme::WHITE << "░" << ColorTheme::RESET;
            }
        }
        
        cout << "] " << ColorTheme::BOLD << int(progress * 100.0) << "%" << ColorTheme::RESET;
        cout.flush();
        
        // Sleep for animation effect
        this_thread::sleep_for(chrono::milliseconds(30));
    }
    
    cout << ColorTheme::GREEN << " ✓" << ColorTheme::RESET << endl;
    cout << endl;
    this_thread::sleep_for(chrono::milliseconds(30));
}

int main() {
    cout << ColorTheme::BOLD << ColorTheme::MAGENTA << "═══════════════════════════════════════════════════════" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::CYAN << "       Welcome to TODO & Event Manager!" << ColorTheme::RESET << endl;
    cout << ColorTheme::BOLD << ColorTheme::MAGENTA << "═══════════════════════════════════════════════════════" << ColorTheme::RESET << endl;
    cout << endl;
    
    // Show loading animation
    showLoadingAnimation();
    
    TodoApp app("my_tasks.dat");
    
    // Optional: Start background alert monitor in separate thread
    // thread alertThread(&TodoApp::startAlertMonitor, &app);
    // alertThread.detach();
    
    app.run();
    
    return 0;
}