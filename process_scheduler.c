/* 
 * Meredith Berenson
 * Operating Systems Project: Process Scheduling Simulation
 * Optimized Version: Step 1 - Read Process Data from a File
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INITIAL_CAPACITY 10
#define BUFFER_SIZE 256

// Define the process structure
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
} Process;

// Dynamically allocate memory for processes
Process* readProcesses(const char* filename, int* process_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file '%s': %s\n", filename, strerror(errno));
        return NULL;
    }

    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, file); // Skip header line

    int capacity = INITIAL_CAPACITY;
    Process* processes = malloc(capacity * sizeof(Process));
    if (!processes) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(file);
        return NULL;
    }

    int count = 0;
    while (fgets(buffer, BUFFER_SIZE, file)) {
        if (count >= capacity) {
            capacity *= 2;
            Process* temp = realloc(processes, capacity * sizeof(Process));
            if (!temp) {
                fprintf(stderr, "Memory reallocation error\n");
                free(processes);
                fclose(file);
                return NULL;
            }
            processes = temp;
        }

        if (sscanf(buffer, "%d %d %d %d",
                   &processes[count].pid,
                   &processes[count].arrival_time,
                   &processes[count].burst_time,
                   &processes[count].priority) != 4) {
            fprintf(stderr, "Warning: Incorrect format in line '%s'\n", buffer);
            continue;
        }
        count++;
    }

    fclose(file);
    *process_count = count;
    return processes;
}

void printProcesses(const Process processes[], int count) {
    printf("PID\tArrival\tBurst\tPriority\n");
    for (int i = 0; i < count; i++) {
        printf("%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].priority);
    }
}

int main() {
    const char* filename = "processes.txt";

    int process_count = 0;
    Process* processes = readProcesses(filename, &process_count);

    if (processes && process_count > 0) {
        printProcesses(processes, process_count);
        free(processes);
    } else {
        fprintf(stderr, "No processes loaded or an error occurred.\n");
    }

    return 0;
}
