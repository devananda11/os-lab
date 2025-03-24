#include <stdio.h>
#include <limits.h>

struct Process {
    int pid, at, bt, ct, tat, wt, completed;
};

// Function to find the next shortest job that has arrived
int findShortestJob(struct Process p[], int n, int currentTime) {
    int minIndex = -1, minBurst = INT_MAX;
    for (int i = 0; i < n; i++) {
        if (!p[i].completed && p[i].at <= currentTime && p[i].bt < minBurst) {
            minBurst = p[i].bt;
            minIndex = i;
        }
    }
    return minIndex;


}

void sjf(struct Process p[], int n) {
    int completed = 0, currentTime = 0;
    int pro[n];
    int times[n];
    int ind=0;
    printf("Gantt Chart\n");

    while (completed < n) {
        int shortest = findShortestJob(p, n, currentTime);
        
        if (shortest == -1) {
            currentTime++;  // If no process has arrived yet, move forward in time
            continue;
        }

        p[shortest].ct = currentTime + p[shortest].bt;  // Completion Time
        p[shortest].tat = p[shortest].ct - p[shortest].at;  // Turnaround Time
        p[shortest].wt = p[shortest].tat - p[shortest].bt;  // Waiting Time
        currentTime = p[shortest].ct;  // Move time forward
        p[shortest].completed = 1;  // Mark process as completed
        completed++;
        pro[ind]=shortest;
        times[ind++]=p[shortest].ct;
    }
    for(int i=0;i<n;i++){
        printf("P%d\t",pro[i]);
    }
    printf("\n");
    for(int i=0;i<n;i++){
        printf("%d\t",times[i]);
    }



}

void display(struct Process p[], int n) {
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Taking user input
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        p[i].pid = i + 1;
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].completed = 0;
    }

    // Apply SJF Scheduling
    sjf(p, n);

    // Display results
    display(p, n);

    return 0;
}
