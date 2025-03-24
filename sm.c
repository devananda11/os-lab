#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

int main()
{
    int shmid;
    key_t key;
    char* shm_ptr;
    pid_t child_pid;

    key=ftok(".",'x');
    if (key==-1){
        perror("ftok");
        exit(1);
    }

    shmid=shmget(key,SHM_SIZE,IPC_CREAT | 0666);
    if (key==-1){
        perror("shmget");
        exit(1);
    }

    child_pid=fork();
    if (child_pid==-1){
        perror("fork");
        exit(1);
    }
    else if (child_pid==0){
        shm_ptr=shmat(shmid,NULL,0);
        if (shm_ptr== char* -1){
            perror("shmat");
            exit(1);
        }
        printf("Child is READING %s\n",shm_ptr);

        if (shmdt(shm_ptr)==-1){
            perror("shmdt");
            exit(1);
        }
        exit(0);
    }
    else{
        shm_ptr=shmat(shmid,NULL,0);
        if (shm_ptr== char* -1){
            perror("shmat");
            exit(1);
        }
        strcpy(shm_ptr,"Parent Writing\n");

        if (shmdt(shm_ptr)==-1){
            perror("shmdt");
            exit(1);
        }
        wait(NULL);
    }

    if (shmctl(shmid,IPC_RMID,NULL)==-1){
        perror("shmctl");
        exit(1);
    }
    exit(0);
}