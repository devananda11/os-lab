#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int completed;
    int status;
    int rem;
};

struct Node {
    struct Process* process;
    struct Node* next;
};

struct Node* front = NULL;
struct Node* rear = NULL;

void enqueue(struct Process* process) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->process = process;
    newNode->next = NULL;

    if (!front)
        front = rear = newNode;
    else {
        rear->next = newNode;
        rear = newNode;
    }
}

struct Process* dequeue() {
    if (!front) return NULL;

    struct Node* temp = front;
    struct Process* process = temp->process;
    front = front->next;
    free(temp);
    return process;
}

void roundRobin(struct Process processes[], int n, int quantum) {
    int completed = 0, currentTime = 0;

    enqueue(&processes[0]);
    processes[0].status = 1;

    printf("\nGantt Chart:\n");

    while (completed < n) {
        if (front) {
            struct Process* temp = dequeue();
            int exec = (temp->rem < quantum) ? temp->rem : quantum;
            temp->rem -= exec;
            currentTime += exec;

            // Check for new arrivals during execution
            for (int i = 0; i < n; i++) {
                if (processes[i].at <= currentTime && processes[i].status != 1 && processes[i].rem > 0) {
                    enqueue(&processes[i]);
                    processes[i].status = 1;
                }
            }

            printf("P%d(%d) ", temp->pid, currentTime);

            if (temp->rem == 0) {
                temp->ct = currentTime;
                completed++;
            } else {
                enqueue(temp);
            }
        } else {
            currentTime++;
        }
    }

    printf("|\n\nProcess  Arrival  Burst  Completion  Turnaround  Waiting\n");

    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        processes[i].tat = processes[i].ct - processes[i].at;
        processes[i].wt = processes[i].tat - processes[i].bt;
        totalWT += processes[i].wt;
        totalTAT += processes[i].tat;

        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",
               processes[i].pid, processes[i].at, processes[i].bt,
               processes[i].ct, processes[i].tat, processes[i].wt);
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);
}

int main() {
    int n, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);

        processes[i].pid = i + 1;
        processes[i].rem = processes[i].bt;
        processes[i].status = 0;
        processes[i].completed = 0;
        processes[i].wt = 0;
        processes[i].tat = 0;
        processes[i].ct = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    roundRobin(processes, n, quantum);

    return 0;
}
