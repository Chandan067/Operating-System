#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void print_odd_numbers(int start, int end)
{
    pid_t pid = getpid();
    printf("Odd Numbers (Process ID: %d):\n", pid);
    for (int i = start; i <= end; i++) {
        if (i % 2 != 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

void print_even_numbers(int start, int end)
{
    pid_t pid = getpid();
    printf("Even Numbers (Process ID: %d):\n", pid);
    for (int i = start; i <= end; i++) {
        if (i % 2 == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

void print_multiples_of_three(int start, int end)
{
    pid_t pid = getpid();
    printf("Multiples of Three (Process ID: %d):\n", pid);
    for (int i = start; i <= end; i++) {
        if (i % 3 == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

void print_multiples_of_five(int start, int end)
{
    pid_t pid = getpid();
    printf("Multiples of Five (Process ID: %d):\n", pid);
    for (int i = start; i <= end; i++) {
        if (i % 5 == 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main()
{
    int start, end;
    printf("Enter the starting number: ");
    scanf("%d", &start);
    printf("Enter the ending number: ");
    scanf("%d", &end);

    pid_t pid1, pid2, pid3, pid4;

    pid1 = fork();
    if (pid1 == 0) {
        print_odd_numbers(start, end);
        return 0;
    }

    pid2 = fork();
    if (pid2 == 0) {
        print_even_numbers(start, end);
        return 0;
    }

    pid3 = fork();
    if (pid3 == 0) {
        print_multiples_of_three(start, end);
        return 0;
    }

    pid4 = fork();
    if (pid4 == 0) {
        print_multiples_of_five(start, end);
        return 0;
    }

    return 0;
}
