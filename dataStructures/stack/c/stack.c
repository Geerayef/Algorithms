#include <stdio.h>
#include <stdbool.h>

#define LOG_ERROR(msg) printf("~~~~~ [ERROR] %s\n", msg)

typedef struct snode {
    int data;
    struct snode *pprevious;
} Snode;
Snode *HEAD;
Snode *TAIL;

enum LENGTH_OPS {
    LENGTH_PUSH = 1,
    LENGTH_POP,
};
int LENGTH = 0;

Snode
create_node(int data)
{
    return (struct snode) { .data = data, .pprevious = NULL };
}

void
init_stack(Snode *node)
{
    HEAD = node;
    TAIL = node;
    if (LENGTH > 0) {
        LOG_ERROR("Call to initialise the stack was just made for the second time. This should not happen.");
        return;
    }
    LENGTH = 1;

    return;
}

int
update_length(int operation)
{
    if (operation == LENGTH_PUSH) {
        LENGTH++;
    }

    if (operation == LENGTH_POP) {
        LENGTH--;
        if (LENGTH < 0) {
            LOG_ERROR("Stack length became negative. This should not happen.");
            return -1;
        }
    }

    return LENGTH;
}

bool
push(Snode *node)
{
    if (HEAD == NULL || TAIL == NULL) {
        LOG_ERROR("Stack is not initialised.");
        return false;
    }

    node->pprevious = HEAD;
    HEAD = node;
    update_length(LENGTH_PUSH);

    printf("~~~~~ Pushed: %d\n", HEAD->data);
    return true;
}

bool
pop()
{
    if (HEAD == NULL || TAIL == NULL) {
        LOG_ERROR("Stack is not initialised.");
        return false;
    }

    if (LENGTH == 0) {
        LOG_ERROR("Invalid operation - stack is empty, cannot pop element from it.");
        return false;
    }
    Snode *old_head = HEAD;
    HEAD = HEAD->pprevious;
    old_head->pprevious = NULL;
    update_length(LENGTH_POP);

    printf("~~~~~ Popped: %d.\n", old_head->data);
    return true;
}

int
peek()
{
    return HEAD->data;
}

void
print_stack()
{
    if (HEAD == NULL || TAIL == NULL) {
        LOG_ERROR("Stack is not initialised.");
        return;
    }

    Snode *current_node = HEAD;
    int i = 0;
    printf("~~~~~ Current stack state: [ ");
    while (i < LENGTH) {
        if (current_node == TAIL) {
            printf("%d ", current_node->data);
            break;
        }
        printf("%d, ", current_node->data);
        i++;
        current_node = current_node->pprevious;
    }
    printf("]\n");

    return;
}

int
main(int argc, char *argv[])
{
    int head_data;
    Snode node_a = create_node(1);
    init_stack(&node_a);

    Snode node_b = create_node(4);
    push(&node_b);

    Snode node_c = create_node(7);
    push(&node_c);

    Snode node_d = create_node(10);
    push(&node_d);

    Snode node_e = create_node(14);
    push(&node_e);

    head_data = peek();
    printf("~~~~~ Peek: HEAD = %d.\n", head_data);

    Snode node_f = create_node(17);
    push(&node_f);

    Snode node_g = create_node(24);
    push(&node_g);

    Snode node_h = create_node(112);
    push(&node_h);

    print_stack();

    pop();
    pop();
    pop();
    pop();

    print_stack();

    head_data = peek();
    printf("~~~~~ Peek: HEAD = %d.\n", head_data);

    return 0;
}
