#include <stdio.h>
#include <stdbool.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

int main() {
    int n, m; // n = number of page references, m = number of page frames
    printf("Enter the number of page references: ");
    scanf("%d", &n);
    printf("Enter the number of page frames: ");
    scanf("%d", &m);

    int pages[MAX_PAGES]; // array to store page references
    printf("\nEnter the page references:\n");
    for(int i=0; i<n; i++) {
        scanf("%d", &pages[i]);
    }

    int frames[MAX_FRAMES]; // array to store page frames
    bool in_frame[MAX_PAGES] = {false}; // array to track if a page is already in a frame

    int hits = 0; // number of page hits
    int faults = 0; // number of page faults
    int counter[MAX_FRAMES] = {0}; // array to store the counter for each frame

    for(int i=0; i<n; i++) {
        int page = pages[i];

        // Check if page is already in a frame
        if(in_frame[page]) {
            hits++;
            counter[page]++; // increment the counter for the page
        } else {
            faults++;

            // Check if there is an empty frame
            int empty_frame = -1;
            for(int j=0; j<m; j++) {
                if(frames[j] == -1) {
                    empty_frame = j;
                    break;
                }
            }

            // If there is an empty frame, use it
            if(empty_frame != -1) {
                frames[empty_frame] = page;
                in_frame[page] = true;
                counter[empty_frame] = i+1; // set the counter for the page to the current time
            } else {
                // Otherwise, find the page that has the smallest counter
                int victim = find_lru_victim(frames, m, counter);
                in_frame[frames[victim]] = false;
                frames[victim] = page;
                in_frame[page] = true;
                counter[victim] = i+1; // set the counter for the page to the current time
            }
        }
    }

    printf("\nHits: %d\nFaults: %d\n", hits, faults);

    return 0;
}

// Find the index of the least recently used page
int find_lru_victim(int frames[], int m, int counter[]) {
    int victim = 0;
    int min_counter = counter[0];
    for(int i=1; i<m; i++) {
        if(counter[i] < min_counter) {
            victim = i;
            min_counter = counter[i];
        }
    }
    return victim;
}

