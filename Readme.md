# TODO & EVENT MANAGER

A feature-rich C++ terminal-based todo and event management application with real-time alerts!

##  Features

### Core Functionality
- **Add Tasks/Events** - Create tasks with detailed information
- **Delete Tasks** - Remove tasks by ID
- **Edit Tasks** - Modify any aspect of a task
- **Mark Complete** - Track completed tasks
- **Persistent Storage** - Tasks are saved to file automatically

### Advanced Features
- **Real-Time Alerts** - Get notified when events are approaching
  - 5-minute warning before event time
  - Alert when event time arrives
  - Audio beep notification
- Visual priority and status indicators
- **Priority Levels** - Low, Medium, High priority tasks
- **Categories** - Organize by work, personal, health, study, etc.
- **Time-Based Sorting** - Tasks sorted by scheduled time
- **Status Tracking** - Pending, Overdue, Completed

##  Quick Start

### Compile
```bash
g++ -std=c++11 -pthread todo_app.cpp -o todo_app
```

### Run
```bash
./todo_app
```

## How to Use

### 1. Add a Task/Event

Choose option `1` from menu, then enter:
- **Title**: Brief task name (e.g., "Team Meeting")
- **Description**: Detailed description
- **Category**: work/personal/health/study/other
- **Date/Time**: Format `YYYY-MM-DD HH:MM` (e.g., "2025-11-08 15:30")
- **Priority**: 1 (Low), 2 (Medium), 3 (High)

Example:
```
Title: Doctor Appointment
Description: Annual health checkup
Category: health
Date and Time: 2025-11-08 14:30
Priority: 3
```

### 2. View All Tasks

Choose option `2` to see all tasks in a formatted table with:
- Task ID
- Title
- Scheduled time
- Category (color-coded)
- Priority level
- Status (Pending/Overdue/Completed)

### 3. Edit a Task

Choose option `3` and enter the Task ID. You can modify:
1. Title
2. Description
3. Category
4. Date/Time
5. Priority
6. Completion status
7. Alert on/off

### 4. Delete a Task

Choose option `4`, enter Task ID, and confirm deletion.

### 5. Mark as Complete

Choose option `5` and enter Task ID to mark it as done.

### 6. Check Alerts

Choose option `6` to manually check for upcoming events.
Alerts are also checked automatically when viewing the main menu.

## 🔔 Alert System

The app monitors your events and alerts you:

### 5-Minute Warning
When an event is within 5 minutes:
```
ALERT! EVENT COMING SOON!
Event: Team Meeting
Time: 2025-11-08 15:30
In: 4 minutes
```

### Event Time Alert
When the event time arrives:
```
EVENT TIME!
Event: Team Meeting
Scheduled: 2025-11-08 15:30
```

Plus an audio beep sound (`\a`)!

## Data Persistence

Tasks are automatically saved to `my_tasks.dat` file:
- Saved after every add, edit, or delete operation
- Loaded automatically when app starts
- Your tasks persist between sessions







