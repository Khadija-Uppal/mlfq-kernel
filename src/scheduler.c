typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority_level; // 0 (High), 1 (Med), 2 (Low)
} Process;

// Example of moving a process down a queue (aging/demotion)
void demote_process(Process *p) {
    if (p->priority_level < 2) {
        p->priority_level++;
        printf("Process %d demoted to Queue %d\n", p->pid, p->priority_level);
    }
}
