#include <stdio.h>

#define LOG_ERROR(msg) printf("~~~~~ [ERROR] %s\n", msg)

typedef struct qnode {
    int data;
    struct qnode *pnext;
} Qnode;

Qnode *HEAD;
Qnode *TAIL;

enum LENGTH_OPS {
    LENGTH_ENQUE = 1,
    LENGTH_DEQUE
};
int LENGTH;

Qnode
create_Qnode(int data)
{
    struct qnode temp = { .data = data, .pnext = NULL };
    return temp;
}

Qnode *
init_queue(Qnode *node)
{
    HEAD = node;
    TAIL = node;
    LENGTH = 1;

    printf("~~~~~ Queue initialised: HEAD = %d.\n", HEAD->data);
    return node;
}

int
update_length(int operation)
{
    if (operation == LENGTH_ENQUE) {
        LENGTH++;
    }
    if (operation == LENGTH_DEQUE) {
        LENGTH--;
        if (LENGTH <= 0) {
            LOG_ERROR("Queue length became negative. This should not happen - something went wrong.");
            return -1;
        }
    }
    return LENGTH;
}

void
enque(Qnode *node)
{
    if (HEAD == NULL || TAIL == NULL) {
        LOG_ERROR("Queue is not initialised.");
        return;
    } 

    TAIL->pnext = node;
    TAIL = node;
    update_length(LENGTH_ENQUE);

    printf("~~~~~ Enqued: %d.\n", TAIL->data);
    return;
}

int
deque()
{
    if (HEAD == NULL || TAIL == NULL) {
        LOG_ERROR("Queue is not initialised.");
        return -1;
    } 

    Qnode *current_head = HEAD;
    HEAD = HEAD->pnext;
    current_head->pnext = NULL;
    update_length(LENGTH_DEQUE);

    printf("~~~~~ Dequed: %d.\n", current_head->data);
    return current_head->data;
}

int
peek()
{
    printf("~~~~~ Queue peek: %d.\n", HEAD->data);
    return HEAD->data;
}

void
print_queue()
{
    if (HEAD == NULL || TAIL == NULL) {
        LOG_ERROR("Queue is not initialised.");
        return;
    }

    Qnode *current_node = HEAD;
    int i = 0;
    printf("~~~~~ Queue: current state: [ ");
    while (i < LENGTH) {
        if (current_node == TAIL) {
            printf("%d", current_node->data);
            break;
        }
        printf("%d, ", current_node->data);
        i++;
        current_node = current_node->pnext;
    }
    printf(" ]\n");
    return;
}

void
print_queue_overview()
{
    printf("~~~~~ Queue length: %d\n", LENGTH);
    printf("~~~~~ Queue HEAD: %d\n", HEAD->data);
    printf("~~~~~ Queue TAIL: %d\n", TAIL->data);
    return;
}

int
main(int argc, char *argv[])
{
    int deque_result;

    Qnode node_a = create_Qnode(1);
    init_queue(&node_a);

    Qnode node_b = create_Qnode(3);
    enque(&node_b);

    Qnode node_c = create_Qnode(5);
    enque(&node_c);

    Qnode node_d = create_Qnode(7);
    enque(&node_d);

    Qnode node_e = create_Qnode(9);
    enque(&node_e);

    Qnode node_f = create_Qnode(13);
    enque(&node_f);

    Qnode node_g = create_Qnode(17);
    enque(&node_g);

    print_queue();

    deque_result = deque();
    deque();
    deque();
    deque();

    print_queue();
    print_queue_overview();

    return 0;
}
