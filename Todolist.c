#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TASKS 100

struct Task {
    char title[100];
    int priority;
    int completed;
};

void addTask();
void viewTasks();
void markTaskComplete();
void deleteTask();
void loadTasks();
void saveTasks();

struct Task tasks[MAX_TASKS];
int taskCount = 0;

int main() {
    int choice;
    loadTasks();

    while (1) {
        printf("\nTo-Do List\n");
        printf("1. Add Task\n2. View Tasks\n3. Mark Task as Done\n4. Delete Task\n5. Exit\n");
        printf("Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear invalid input
            printf("Invalid choice! Try again.\n");
            continue;
        }

        switch (choice) {
            case 1: 
                addTask(); 
                break; 
            case 2: 
                viewTasks(); 
                break;
            case 3: 
                markTaskComplete(); 
                break;
            case 4: 
                deleteTask(); 
                break; 
            case 5: 
                saveTasks(); 
                exit(0);
            default: 
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void loadTasks() {
    FILE *file = fopen("tasks.txt", "r");
    if (file) {
        while (taskCount < MAX_TASKS && fscanf(file, "%[^,],%d,%d\n", tasks[taskCount].title,
               &tasks[taskCount].priority, &tasks[taskCount].completed) != EOF) {
            taskCount++;
        }
        fclose(file);
    }
}

void saveTasks() {
    FILE *file = fopen("tasks.txt", "w");
    if (file) {
        for (int i = 0; i < taskCount; i++) {
            fprintf(file, "%s,%d,%d\n", tasks[i].title, tasks[i].priority, tasks[i].completed);
        }
        fclose(file);
    } else {
        printf("Error opening file for saving.\n");
    }
}

void addTask() {
    if (taskCount < MAX_TASKS) {
        struct Task task;
        printf("Enter task title: ");
        getchar(); // Clear the newline from the input buffer
        fgets(task.title, sizeof(task.title), stdin);
        task.title[strcspn(task.title, "\n")] = 0;

        printf("Enter priority (1-5): ");
        if (scanf("%d", &task.priority) != 1 || task.priority < 1 || task.priority > 5) {
            while (getchar() != '\n'); // Clear invalid input
            printf("Invalid priority! Try again.\n");
            return;
        }

        task.completed = 0;
        tasks[taskCount++] = task;
        saveTasks();
        printf("Task added successfully!\n");
    } else {
        printf("Task list is full!\n");
    }
}

void viewTasks() {
    printf("\nYour Tasks:\n");
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }
    for (int i = 0; i < taskCount; i++) {
        printf("%d. [%s] Priority: %d - %s\n", i + 1, tasks[i].completed ? "X" : " ", tasks[i].priority, tasks[i].title);
    }
}

void markTaskComplete() {
    int taskIndex;
    viewTasks();
    printf("Enter the task number to mark as complete: ");
    if (scanf("%d", &taskIndex) != 1 || taskIndex < 1 || taskIndex > taskCount) {
        while (getchar() != '\n'); // Clear invalid input
        printf("Invalid task number! Try again.\n");
        return;
    }

    tasks[taskIndex - 1].completed = 1;
    saveTasks();
    printf("Task marked as complete!\n");
}

void deleteTask() {
    int taskIndex;
    viewTasks();
    printf("Enter the task number to delete: ");
    if (scanf("%d", &taskIndex) != 1 || taskIndex < 1 || taskIndex > taskCount) {
        while (getchar() != '\n'); // Clear invalid input
        printf("Invalid task number! Try again.\n");
        return;
    }

    for (int i = taskIndex - 1; i < taskCount - 1; i++) {
        tasks[i] = tasks[i + 1];
    }
    taskCount--;
    saveTasks();
    printf("Task deleted successfully!\n");
}