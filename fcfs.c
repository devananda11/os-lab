#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt;
};

// Function to sort processes by Arrival Time (AT)
void sortByArrivalTime(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }


}

void fcfs(struct Process p[], int n) {
    int currentTime = 0;
    printf("Gantt Chart\n");
    int pro[n];
    int times[n];
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at) {
            currentTime = p[i].at;  // CPU remains idle if process hasn't arrived
        }
        p[i].ct = currentTime + p[i].bt;  // Completion Time
        p[i].tat = p[i].ct - p[i].at;     // Turnaround Time
        p[i].wt = p[i].tat - p[i].bt;     // Waiting Time
        currentTime = p[i].ct;            // Update current time
        
        pro[i]=i;
        times[i]=p[i].ct;
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
    }
    
    // Sort by Arrival Time and Apply FCFS
    sortByArrivalTime(p, n);
    fcfs(p, n);
    
    // Display results
    display(p, n);
    
    return 0;
}
