#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // For fork(), sleep()
#include <sys/ipc.h>  // For IPC (Inter-Process Communication)
#include <sys/shm.h>  // For shared memory functions
#include <sys/wait.h> // For wait()
#include <string.h>   // For strcpy()

#define SHM_SIZE 1024  // Shared memory segment size (1KB)

int main() {
    int shmid;
    key_t key;
    char *shm_ptr;
    pid_t child_pid;

    // Generate a unique key for the shared memory segment
    key = ftok(".", 'x');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Fork a child process
    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(1);
    } else if (child_pid == 0) {
        // Child process (Reader)

        // Attach to the shared memory segment
        shm_ptr = shmat(shmid, NULL, 0);
        if (shm_ptr == (char *)-1) {
            perror("shmat");
            exit(1);
        }

        // Read and print data from the shared memory
        printf("Child process (Reader) reads: %s\n", shm_ptr);

        // Detach from shared memory
        if (shmdt(shm_ptr) == -1) {
            perror("shmdt");
            exit(1);
        }

        exit(0);
    } else {
        // Parent process (Writer)

        // Attach to the shared memory segment
        shm_ptr = shmat(shmid, NULL, 0);
        if (shm_ptr == (char *)-1) {
            perror("shmat");
            exit(1);
        }

        // Write data to shared memory
        strcpy(shm_ptr, "Hello from the parent process (Writer)!");

        // Detach from shared memory
        if (shmdt(shm_ptr) == -1) {
            perror("shmdt");
            exit(1);
        }

        // Wait for child process to finish
        wait(NULL);
    }

    // Mark the shared memory segment for deletion
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    return 0;
}
