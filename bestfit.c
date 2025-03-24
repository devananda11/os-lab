#include <stdio.h>
#include <stdlib.h>
struct Block{
    int pid;
    int size;
    struct Block* next;
} ;
struct Block* createBlocks(int n){
    struct Block* head=NULL, *tail=NULL, *newBlock;
    int size;
    for(int i=0;i<n;i++){
        printf("Enter size of block %d: ", i + 1);
        scanf("%d", &size);
        newBlock=(struct Block*)malloc(sizeof(struct Block));
        newBlock->size=size;
        newBlock->pid=-1;
        newBlock->next=NULL;
        if (head == NULL){
            head=newBlock;
            tail=newBlock;
        }
        else{
            tail->next=newBlock;
            tail=newBlock;
        }
    }
    return head;
}
void bestFirst(struct Block* memory,int pid,int psize){
    struct Block* temp=memory;
    int best=9999;
    struct Block* bestBlock=NULL;
    while ( temp ){
        if ( temp->pid == -1 && temp->size >= psize){
            if (temp->size < best){
                best=temp->size;
                bestBlock=temp;
            }
        }
        temp=temp->next;
    }
    if (bestBlock)
    bestBlock->pid = pid;

}
void display(struct Block* head) {
    printf("\nMemory Allocation (Best-Fit):\n");

    printf("Block Size\tProcess ID\n");
    while (head) {
        printf("%d\t\t", head->size);
        if (head->pid == -1)
            printf("Not Allocated\n");
        else
            printf("Process %d\n", head->pid);
        head = head->next;
    }
}
int main(){
    int block,m;
    printf("Enter no of blocks\n");
    scanf("%d",&block);
    struct Block* memory=createBlocks(block);
    printf("Enter number of processes: ");
    scanf("%d", &m);
    int process_sizes[m];

    for (int i = 0; i < m; i++) {
        printf("Enter size of process %d: ", i + 1);
        scanf("%d", &process_sizes[i]);
    }

    for (int i = 0; i < m; i++)
        bestFirst(memory, i + 1, process_sizes[i]);

    display(memory);
    return 0;

}
