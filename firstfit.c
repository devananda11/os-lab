#include <stdio.h>
#include <stdlib.h>

struct Block {
    int size;
    int process_id;
    struct Block* next;
};

struct Block* createBlocks(int n) {
    struct Block *head = NULL, *temp = NULL, *newBlock;
    int size;
    
    for (int i = 0; i < n; i++) {
        printf("Enter size of block %d: ", i + 1);
        scanf("%d", &size);

        newBlock = (struct Block*)malloc(sizeof(struct Block));
        newBlock->size = size;
        newBlock->process_id = -1;
        newBlock->next = NULL;

        if (head == NULL)
            head = newBlock;
        else
            temp->next = newBlock;

        temp = newBlock;
    }
    return head;
}

void firstFit(struct Block* head, int process_id, int process_size) {
    struct Block* temp = head;
    while (temp) {
        if (temp->process_id == -1 && temp->size >= process_size) {
            temp->process_id = process_id;
            return;
        }
        temp = temp->next;
    }
}

void display(struct Block* head) {
    printf("\nMemory Allocation (First-Fit):\n");
    printf("Block Size\tProcess ID\n");
    while (head) {
        printf("%d\t\t", head->size);
        if (head->process_id == -1)
            printf("Not Allocated\n");
        else
            printf("Process %d\n", head->process_id);
        head = head->next;
    }
}

int main() {
    int n, m;
    printf("Enter number of memory blocks: ");
    scanf("%d", &n);
    struct Block* memory = createBlocks(n);

    printf("Enter number of processes: ");
    scanf("%d", &m);
    int process_sizes[m];

    for (int i = 0; i < m; i++) {
        printf("Enter size of process %d: ", i + 1);
        scanf("%d", &process_sizes[i]);
    }

    for (int i = 0; i < m; i++)
        firstFit(memory, i + 1, process_sizes[i]);

    display(memory);
    return 0;
}
