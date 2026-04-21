#include <stdio.h>

#define MAX 100

// Function declarations
void fcfs(int n, int at[], int bt[]);
void sjf(int n, int at[], int bt[]);
void roundRobin(int n, int at[], int bt[], int tq);

// ---------------- MAIN ----------------
int main() {
    int n, choice, tq;
    int at[MAX], bt[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Process %d Arrival Time: ", i+1);
        scanf("%d", &at[i]);
        printf("Process %d Burst Time: ", i+1);
        scanf("%d", &bt[i]);
    }

    while(1) {
        printf("\n--- CPU Scheduling Menu ---\n");
        printf("1. FCFS\n2. SJF\n3. Round Robin\n4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                fcfs(n, at, bt);
                break;
            case 2:
                sjf(n, at, bt);
                break;
            case 3:
                printf("Enter Time Quantum: ");
                scanf("%d", &tq);
                roundRobin(n, at, bt, tq);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}

// ---------------- FCFS ----------------
void fcfs(int n, int at[], int bt[]) {
    int ct[MAX], tat[MAX], wt[MAX];

    ct[0] = at[0] + bt[0];

    for(int i = 1; i < n; i++) {
        if(ct[i-1] < at[i])
            ct[i] = at[i] + bt[i];
        else
            ct[i] = ct[i-1] + bt[i];
    }

    printf("\n--- FCFS Result ---\n");
    printf("P\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
}

// ---------------- SJF ----------------
void sjf(int n, int at[], int bt[]) {
    int ct[MAX], tat[MAX], wt[MAX];
    int done[MAX] = {0};
    int time = 0, completed = 0;

    while(completed < n) {
        int min = 9999, index = -1;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && !done[i] && bt[i] < min) {
                min = bt[i];
                index = i;
            }
        }

        if(index == -1) {
            time++;
            continue;
        }

        time += bt[index];
        ct[index] = time;
        done[index] = 1;
        completed++;
    }

    printf("\n--- SJF Result ---\n");
    printf("P\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
}

// ---------------- ROUND ROBIN ----------------
void roundRobin(int n, int at[], int bt[], int tq) {
    int rem_bt[MAX], ct[MAX], tat[MAX], wt[MAX];
    int time = 0, remain = n;

    for(int i = 0; i < n; i++)
        rem_bt[i] = bt[i];

    while(remain > 0) {
        for(int i = 0; i < n; i++) {
            if(rem_bt[i] > 0) {
                if(rem_bt[i] <= tq) {
                    time += rem_bt[i];
                    rem_bt[i] = 0;
                    ct[i] = time;
                    remain--;
                } else {
                    rem_bt[i] -= tq;
                    time += tq;
                }
            }
        }
    }

    printf("\n--- Round Robin Result ---\n");
    printf("P\tAT\tBT\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], ct[i], tat[i], wt[i]);
    }
}
