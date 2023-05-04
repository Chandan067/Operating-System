#include <stdio.h>

// Process structure
struct Process {
    int pid; // process ID
    int priority; // process priority
    int burst_time; // process burst time
    int remaining_time; // remaining burst time
};

// Function to swap two processes
void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n; // number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input the process details
    for(int i=0; i<n; i++) 
	{
        printf("Enter the process ID, priority and burst time of process %d: ", i+1);
        scanf("%d %d %d", &processes[i].pid, &processes[i].priority, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    // Sort the processes based on their priority
    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(processes[j].priority > processes[j+1].priority) {
                swap(&processes[j], &processes[j+1]);
            }
        }
    }

    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    printf("\nGantt Chart:\n");
    printf("%d", current_time);

    // Run the processes in a preemptive manner based on their priority
    while(1) {
        int process_found = 0;
        for(int i=0; i<n; i++) {
            if(processes[i].remaining_time > 0 && processes[i].priority <= processes[0].priority) {
                processes[i].remaining_time--;
                current_time++;
                printf(" | P%d | %d", processes[i].pid, current_time);
                if(processes[i].remaining_time == 0) {
                    process_found = 1;
                    int turnaround_time = current_time - processes[i].burst_time;
                    int waiting_time = turnaround_time - processes[i].burst_time;
                    total_waiting_time += waiting_time;
                    total_turnaround_time += turnaround_time;
                }
                break;
            }
        }
        if(process_found == 0) {
            current_time++;
            printf(" | IDLE | %d", current_time);
        }
        if(current_time == 100) { // maximum time limit to avoid infinite loop
            break;
        }
    }

    // Calculate and display the average waiting time and average turnaround time
    float avg_waiting_time = (float)total_waiting_time/n;
    float avg_turnaround_time = (float)total_turnaround_time/n;

    printf("\n\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f", avg_turnaround_time);

    return 0;
}

