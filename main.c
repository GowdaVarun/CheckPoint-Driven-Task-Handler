#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define MAX_TASKS 10
#define CRASH_FLAG_FILE "crash_flag.txt"
#define CHECKPOINT_FILE "checkpoint.txt"

// Function to check if crash is simulated
bool isCrashSimulated() {
    FILE *file = fopen(CRASH_FLAG_FILE, "r");
    if (file) {
        fclose(file);
        return true; // Crash flag exists
    }
    return false;
}

// Function to clear crash flag
void clearCrashFlag() {
    remove(CRASH_FLAG_FILE); // Remove crash flag file
}

// Function to set the crash flag
void setCrashFlag() {
    FILE *file = fopen(CRASH_FLAG_FILE, "w");
    if (file) {
        fprintf(file, "1"); // Write anything to indicate crash
        fclose(file);
    }
}

// Function to process tasks and update the checkpoint file
void processTasks(int start) {
    FILE *file = fopen(CHECKPOINT_FILE, "w");
    if (!file) {
        perror("Error opening checkpoint file");
        exit(1);
    }

    for (int i = start; i < MAX_TASKS; i++) {
        if (isCrashSimulated()) {
            printf("Crash detected. Stopping task processing. Last checkpoint saved at task %d.\n", i);
            break;
        }

        printf("Processing task %d...\n", i + 1);
        fprintf(file, "%d\n", i); // Save the task ID as a checkpoint
        fflush(file); // Ensure data is written to the file
        sleep(1); // Simulate time delay for each task
    }

    fclose(file);
    if (!isCrashSimulated()) {
        printf("All tasks completed successfully!\n");
    }
}

int getCheckpoint() {
    FILE *file = fopen(CHECKPOINT_FILE, "r");
    if (!file) {
        return 0; // If no checkpoint file exists, start from the beginning
    }

    int lastTask = 0;
    int temp = 0;

    // Read through the file to get the last task ID
    while (fscanf(file, "%d", &temp) == 1) {
        lastTask = temp;
    }

    fclose(file);
    return lastTask; // Return the last task ID
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <start|recover|crash>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "start") == 0) {
        printf("Starting tasks from the beginning...\n");
        clearCrashFlag(); // Clear crash flag before starting
        processTasks(0);
    } else if (strcmp(argv[1], "recover") == 0) {
        int checkpoint = getCheckpoint();
        printf("Recovering tasks from checkpoint %d...\n", checkpoint + 1);
        clearCrashFlag(); // Clear crash flag before recovering
        processTasks(checkpoint);
    } else if (strcmp(argv[1], "crash") == 0) {
        printf("Simulating a crash...\n");
        setCrashFlag(); // Set crash flag
    } else {
        printf("Invalid option. Use <start|recover|crash>.\n");
        return 1;
    }

    return 0;
}
