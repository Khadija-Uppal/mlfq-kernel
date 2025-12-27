#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define Q0_QUANTUM 4
#define Q1_QUANTUM 8

typedef struct {
    int pid;
    int burst_time;
    int remaining_time;
    int priority; // 0: High, 1: Med, 2: Low
    int arrival_time;
    int wait_time;
    int turnaround_time;
} Process;

void boot_sequence() {
    system("clear");
    printf("\033[1;36m==========================================\n");
    printf("        KALI-KERNEL MLFQ v2.0 READY       \n");
    printf("==========================================\n\033[0m");
    char *steps[] = {"Loading Scheduler...", "Setting Quantums (Q0:4ms, Q1:8ms)...", "Ready for Input..."};
    for (int i = 0; i < 3; i++) {
        printf("[ OK ] %s\n", steps[i]);
        usleep(500000);
    }
}

void display_visuals(Process proc[], int n, int current_time, int active_pid) {
    system("clear");
    printf("\033[1;33mKernel Time: %d ms\033[0m\n", current_time);
    printf("-------------------------------------------------------------------\n");
    printf("PID\tQueue\tRemaining\tProgress\n");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%d\tQ%d\t%d ms\t\t", proc[i].pid, proc[i].priority, proc[i].remaining_time);
        int progress = ((proc[i].burst_time - proc[i].remaining_time) * 10) / proc[i].burst_time;
        printf("[");
        for (int j = 0; j < 10; j++) printf(j < progress ? "#" : " ");
        printf("]");
        if (proc[i].pid == active_pid) printf(" \033[1;31mRUNNING\033[0m");
        else if (proc[i].remaining_time == 0) printf(" \033[1;32mDONE\033[0m");
        printf("\n");
    }
}

int main() {
    boot_sequence();
    int n;
    printf("\nEnter number of processes: ");
    scanf("%d", &n);
    
    Process *proc = malloc(n * sizeof(Process));
    for(int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &proc[i].burst_time);
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].priority = 0;
        proc[i].wait_time = 0;
    }

    int current_time = 0, completed = 0;
    while (completed < n) {
        int best = -1;
        // Priority Selection (Q0 > Q1 > Q2)
        for (int i = 0; i < n; i++) {
            if (proc[i].remaining_time > 0) {
                if (best == -1 || proc[i].priority < proc[best].priority) 
                    best = i;
            }
        }

        if (best != -1) {
            int quantum = (proc[best].priority == 0) ? Q0_QUANTUM : (proc[best].priority == 1 ? Q1_QUANTUM : proc[best].remaining_time);
            int run_time = (proc[best].remaining_time < quantum) ? proc[best].remaining_time : quantum;

            for(int t = 0; t < run_time; t++) {
                display_visuals(proc, n, current_time, proc[best].pid);
                usleep(200000); 
                proc[best].remaining_time--;
                current_time++;
                
                // Calculate waiting time for others
                for(int i = 0; i < n; i++) {
                    if(i != best && proc[i].remaining_time > 0) proc[i].wait_time++;
                }
            }

            if (proc[best].remaining_time == 0) completed++;
            else if (proc[best].priority < 2) proc[best].priority++; // Feedback: Demote
        }
    }

    // Final Report Table
    system("clear");
    printf("\033[1;32mExecution Complete!\033[0m\n\n");
    printf("PID\tBurst\tWaiting\tTurnaround\n");
    float avg_w = 0, avg_t = 0;
    for(int i = 0; i < n; i++) {
        int tat = proc[i].burst_time + proc[i].wait_time;
        printf("%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].burst_time, proc[i].wait_time, tat);
        avg_w += proc[i].wait_time; avg_t += tat;
    }
    printf("\nAvg Waiting Time: %.2f | Avg Turnaround: %.2f\n", avg_w/n, avg_t/n);
    
    free(proc);
    return 0;
}
