#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
typedef struct {
    int name, arrival, burst, remaining, status, completion, waiting, turnaround;
} Process;

// Structure to represent a node in the waiting queue
typedef struct Node {
    Process process;
    struct Node* next;
} Node;

Node *front = NULL, *rear = NULL;

// Function to enqueue a process into the waiting queue
void enqueue(Process process) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->process = process;
    newNode->next = NULL;

    if (!front)
        front = rear = newNode;
    else {
        rear->next = newNode;
        rear = newNode;
    }
}

// Function to dequeue a process from the waiting queue
Process dequeue() {
    Node* temp = front;
    Process process = temp->process;
    front = front->next;
    free(temp);
    return process;
}

// Round Robin Scheduling function
void roundRobin(Process processes[], int n, int quantum) {
    int currentTime = 0, completed = 0;
    
    printf("\nGantt Chart:\n");

    // Enqueue first process
    enqueue(processes[0]);
    processes[0].status = 1;

    while (completed < n) {
        if (front) {
            Process currentProcess = dequeue();
            int executionTime = (currentProcess.remaining < quantum) ? currentProcess.remaining : quantum;
            currentProcess.remaining -= executionTime;
            currentTime += executionTime;

            // Check for new arrivals
            for (int i = 0; i < n; i++) {
                if (processes[i].arrival <= currentTime && !processes[i].status) {
                    enqueue(processes[i]);
                    processes[i].status = 1;
                }
            }

            printf("| P%d %2d ", currentProcess.name, currentTime);

            if (currentProcess.remaining == 0) {
                completed++;
                for (int i = 0; i < n; i++)
                    if (processes[i].name == currentProcess.name)
                        processes[i].completion = currentTime;
            } else {
                enqueue(currentProcess);
            }
        } else {
            currentTime++;
        }
    }

    printf("|\n\nProcess  Arrival  Burst  Completion  Turnaround  Waiting\n");

    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        processes[i].turnaround = processes[i].completion - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst;
        totalWT += processes[i].waiting;
        totalTAT += processes[i].turnaround;

        printf("P%-7d %-7d %-6d %-10d %-10d %-6d\n",
               processes[i].name, processes[i].arrival, processes[i].burst,
               processes[i].completion, processes[i].turnaround, processes[i].waiting);
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);
}

int main() {
    int n, quantum;

    // User input for number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    // User input for process details
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
        
        // Assign values individually
        processes[i].name = i + 1;
        processes[i].remaining = processes[i].burst;
        processes[i].status = 0;
        processes[i].completion = -1;
        processes[i].waiting = 0;
        processes[i].turnaround = 0;
    }

    // Quantum time input
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Run Round Robin scheduling
    roundRobin(processes, n, quantum);

    return 0;
}
