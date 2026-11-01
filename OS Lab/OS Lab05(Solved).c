
/* Task 01 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int arr[100];
    int n = argc - 1;
    int i;

    if (n <= 0)
    {
        printf("Enter integers in command line.\n");
        return 1;
    }

    for (i = 0; i < n; i++)
    {
        arr[i] = atoi(argv[i + 1]);
    }

    int pipe1[2];
    int pipe2[2];
    int pipe3[2];
    int pipe4[2];

    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3);
    pipe(pipe4);

    if (fork() == 0)
    {
        close(pipe1[1]);
        close(pipe2[0]);

        int numbers[100];
        int size;

        read(pipe1[0], &size, sizeof(size));
        read(pipe1[0], numbers, size * sizeof(int));

        int sum = 0;

        for (i = 0; i < size; i++)
        {
            sum += numbers[i];
        }

        write(pipe2[1], &sum, sizeof(sum));

        close(pipe1[0]);
        close(pipe2[1]);

        exit(0);
    }

    if (fork() == 0)
    {
        close(pipe3[1]);
        close(pipe4[0]);

        int numbers[100];
        int size;

        read(pipe3[0], &size, sizeof(size));
        read(pipe3[0], numbers, size * sizeof(int));

        int min = numbers[0];

        for (i = 1; i < size; i++)
        {
            if (numbers[i] < min)
            {
                min = numbers[i];
            }
        }

        write(pipe4[1], &min, sizeof(min));

        close(pipe3[0]);
        close(pipe4[1]);

        exit(0);
    }

    close(pipe1[0]);
    close(pipe2[1]);
    close(pipe3[0]);
    close(pipe4[1]);

    write(pipe1[1], &n, sizeof(n));
    write(pipe1[1], arr, n * sizeof(int));

    write(pipe3[1], &n, sizeof(n));
    write(pipe3[1], arr, n * sizeof(int));

    int sum;
    int min;

    read(pipe2[0], &sum, sizeof(sum));
    read(pipe4[0], &min, sizeof(min));

    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe3[1]);
    close(pipe4[0]);

    wait(NULL);
    wait(NULL);

    printf("Sum = %d\n", sum);
    printf("Minimum = %d\n", min);

    return 0;
}
