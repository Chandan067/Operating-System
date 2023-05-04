#include <stdio.h>

int main() {
    int n; // number of memory blocks
    printf("Enter the number of memory blocks: ");
    scanf("%d", &n);

    int memory_blocks[n];
    for(int i=0; i<n; i++) {
        printf("Enter the size of memory block %d: ", i+1);
        scanf("%d", &memory_blocks[i]);
    }

    int m; // number of processes
    printf("\nEnter the number of processes: ");
    scanf("%d", &m);

    int processes[m];
    for(int i=0; i<m; i++) {
        printf("Enter the size of process %d: ", i+1);
        scanf("%d", &processes[i]);
    }

    int allocation[m]; // array to store memory block allocation for each process
    for(int i=0; i<m; i++) {
        allocation[i] = -1; // initialize allocation to -1 (not allocated)
    }

    // Allocate memory blocks to processes using worst fit algorithm
    for(int i=0; i<m; i++) {
        int worst_fit = -1;
        for(int j=0; j<n; j++) {
            if(memory_blocks[j] >= processes[i]) {
                if(worst_fit == -1 || memory_blocks[j] > memory_blocks[worst_fit]) {
                    worst_fit = j;
                }
            }
        }
        if(worst_fit != -1) {
            allocation[i] = worst_fit;
            memory_blocks[worst_fit] -= processes[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for(int i=0; i<m; i++) {
        printf("%d\t\t%d\t\t", i+1, processes[i]);
        if(allocation[i] != -1) {
            printf("%d", allocation[i]+1);
        } else {
            printf("Not Allocated");
        }
        printf("\n");
    }

    return 0;
}

