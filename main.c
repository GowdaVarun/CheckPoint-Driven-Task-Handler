#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep()
#include <string.h> // For strcmp()

#define MAX_TASKS 10
#define CHECKPOINT_FILE "checkpoint.txt"

// Function to process tasks
void processTasks(int start) {
    FILE *file = fopen(CHECKPOINT_FILE, "w");
    if (!file) {
        perror("Error opening checkpoint file");
        exit(1);
    }
    for (int i = start; i < MAX_TASKS; i++) {
        printf("Processing task %d...\n", i + 1);
        fprintf(file, "%d\n", i); // Save the task ID as a checkpoint
        fflush(file); // Ensure data is written to the file
        sleep(1);     // Simulate time delay for each task
    }
    fclose(file);
    printf("All tasks completed successfully!\n");
    // Clear the checkpoint file to indicate all tasks are done
    remove(CHECKPOINT_FILE);
}

// Function to retrieve the last checkpoint
int getCheckpoint() {
    FILE *file = fopen(CHECKPOINT_FILE, "r");
    if (!file) return 0; // If no checkpoint file exists, start from the beginning
    int lastTask = 0, temp = 0;
    while (fscanf(file, "%d", &temp) != EOF) {
        lastTask = temp; // Keep updating to the last read integer
    }

    fclose(file);
    return lastTask;// Resume from the next task
}

int main(int argc, char *argv[]) {
    printf("Checkpoint-Driven Task Handler\n");

    if (argc < 2) {
        printf("Usage: %s [start|crash|recover]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "start") == 0) {
        // Reset the checkpoint and start from task 1
        remove(CHECKPOINT_FILE); // Remove any existing checkpoint
        printf("Starting tasks from the beginning...\n");
        processTasks(0);
    } else if (strcmp(argv[1], "crash") == 0) {
        // Simulate a crash by stopping execution
        printf("Simulating a crash... Program exiting.\n");
        exit(1);
    } else if (strcmp(argv[1], "recover") == 0) {
        // Recover from the last saved checkpoint
        int checkpoint = getCheckpoint();
        printf("Resuming from task %d...\n", checkpoint + 1);
        processTasks(checkpoint);
    } else {
        printf("Invalid command. Use [start|crash|recover].\n");
        return 1;
    }

    return 0;
}
