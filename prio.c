#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id, arrival, burst, priority, waiting, turnaround, completed;
};

int findNextProcess(struct Process p[], int n, int currentTime) {
    int minPriority = 9999, index = -1;

    for (int i = 0; i < n; i++) {
        if (!p[i].completed && p[i].arrival <= currentTime) {
            if (p[i].priority < minPriority) { 
                minPriority = p[i].priority;
                index = i;
            }
        }
    }
    return index;
}

void calculateTimes(struct Process p[], int n) {
    int currentTime = 0, completedProcesses = 0;

    while (completedProcesses < n) {
        int index = findNextProcess(p, n, currentTime);

        if (index == -1) { 
            currentTime++; 
        } else {
            // Process execution
            p[index].waiting = currentTime - p[index].arrival;
            p[index].turnaround = p[index].waiting + p[index].burst;
            currentTime += p[index].burst;
            p[index].completed = 1; // Mark process as completed
            completedProcesses++;
        }
    }
}

void display(struct Process p[], int n) {
    printf("\nID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].priority, p[i].waiting, p[i].turnaround);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", p[i].id);
        scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].priority);
        p[i].completed = 0; // Mark all as not completed
    }

    calculateTimes(p, n);
    display(p, n);

    return 0;
}
