#include "ColorTheme.h"

// Initialize static constants
const std::string ColorTheme::RESET = "\033[0m";
const std::string ColorTheme::RED = "\033[31m";
const std::string ColorTheme::GREEN = "\033[32m";
const std::string ColorTheme::YELLOW = "\033[33m";
const std::string ColorTheme::BLUE = "\033[34m";
const std::string ColorTheme::MAGENTA = "\033[35m";
const std::string ColorTheme::CYAN = "\033[36m";
const std::string ColorTheme::WHITE = "\033[37m";
const std::string ColorTheme::BOLD = "\033[1m";
const std::string ColorTheme::BG_RED = "\033[41m";
const std::string ColorTheme::BG_GREEN = "\033[42m";
const std::string ColorTheme::BG_YELLOW = "\033[43m";

std::string ColorTheme::getPriorityColor(int priority) {
    if (priority == 3) return RED;
    else if (priority == 2) return YELLOW;
    else return GREEN;
}

std::string ColorTheme::getCategoryColor(const std::string& category) {
    if (category == "work") return BLUE;
    else if (category == "personal") return GREEN;
    else if (category == "health") return RED;
    else if (category == "study") return MAGENTA;
    else return CYAN;
}

std::string ColorTheme::getPriorityString(int priority) {
    if (priority == 3) return RED + "HIGH  " + RESET;
    else if (priority == 2) return YELLOW + "MEDIUM" + RESET;
    else return GREEN + "LOW   " + RESET;
}