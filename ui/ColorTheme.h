#ifndef COLORTHEME_H
#define COLORTHEME_H

#include <string>

class ColorTheme {
public:
    // ANSI color codes
    static const std::string RESET;
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string BLUE;
    static const std::string MAGENTA;
    static const std::string CYAN;
    static const std::string WHITE;
    static const std::string BOLD;
    static const std::string BG_RED;
    static const std::string BG_GREEN;
    static const std::string BG_YELLOW;
    
    // Utility methods
    static std::string getPriorityColor(int priority);
    static std::string getCategoryColor(const std::string& category);
    static std::string getPriorityString(int priority);
};

#endif // COLORTHEME_H
