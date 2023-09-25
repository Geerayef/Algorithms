#include <stdio.h>
#include <stdbool.h>

#define LOG_ERROR(msg) printf("~~~~~ [ERROR] %s\n", msg)

struct Node {
    int data;
    struct Node *pnext;
    struct Node *pprevious;
};

struct Node *HEAD = NULL;
struct Node *TAIL = NULL;

enum LENGTH_OPS {                       
    LENGTH_INSERT = 1,
    LENGTH_DELETE,
};
int LENGTH = 0;

void
update_length(int operation)
{
    operation == LENGTH_INSERT ? LENGTH++ : LENGTH--;
    return;
}

struct Node
create_node(int data)
{
    if (LENGTH == 0) {
        LENGTH = 1;
    }
    struct Node temp;
    temp.data = data;
    temp.pnext = NULL;
    temp.pprevious = NULL;

    return temp;
}

bool
append(struct Node *node)
{
    if (node == NULL) {
        LOG_ERROR("Null pointer: The given pointer to the element to append is null.");
        return false;
    }

    if (TAIL == NULL) {
        LOG_ERROR("Linked list is not initialised.");
        return false;
    }

    struct Node *last_node = TAIL;
    last_node->pnext = node;
    node->pprevious = last_node;
    node->pnext = NULL;
    TAIL = node;

    update_length(LENGTH_INSERT);

    printf("~~~~~ Inserted %d.\n", node->data);
    return true;
}

bool
insert_at(struct Node *node, int position)
{
    if (HEAD == NULL || TAIL == NULL) {
        LOG_ERROR("Linked list is not initialised.");
        return false;
    }

    if (node == NULL) {
        LOG_ERROR("Null pointer: The given pointer to the element to be inserted is null.");
        return false;
    }

    if (position > LENGTH) {
        LOG_ERROR("Index out of bounds: The given position, to insert new element at,\
                is bigger than the length of the linked list.");
        return false;
    }

    struct Node *current_node = HEAD;
    int i = 0;
    while (i < position) {
        i++;
        if (current_node->pnext == NULL) {
            break;
        }
        current_node = current_node->pnext;
    }

    if (i < position) {
        LOG_ERROR("Index out of bounds. There are not enough elements in the list.");
        return false;
    } else if (i == position && current_node == TAIL) {
        append(node);
        return true;
    } else {
        struct Node *temp = current_node->pnext;
        current_node->pnext = node;
        node->pprevious = current_node;
        node->pnext = temp;
        temp->pprevious = node;

        update_length(LENGTH_INSERT);
    }

    printf("~~~~~ Inserted %d.\n", node->data);
    return true;
}

bool
delete_node(struct Node *node)
{
    if (HEAD == NULL || TAIL == NULL) {
        LOG_ERROR("Linked list is not initialised.");
        return false;
    }

    if (node == NULL) {
        LOG_ERROR("Null pointer: The given pointer to the node to be deleted is null.");
        return false;
    } else if (node->pnext == NULL) {
        LOG_ERROR("Null pointer: The pointer to the next node, from the given node, is null - and the given node to be deleted is not HEAD.");
        return false;
    } else if (node->pprevious == NULL) {
        LOG_ERROR("Null pointer: The pointer to the previous node, from the given node, is null - and the given node to be deleted is not TAIL.");
        return false;
    }

    if (node == HEAD) {
        HEAD = node->pnext;
        HEAD->pprevious = NULL;
        node->pnext = NULL;
        update_length(LENGTH_DELETE);
        printf("~~~~~ Deleted %d.\n", node->data);
        return true;
    }

    if (node == TAIL) {
        TAIL = node->pprevious;
        TAIL->pnext = NULL;
        node->pprevious = NULL;
        update_length(LENGTH_DELETE);
        printf("~~~~~ Deleted %d.\n", node->data);
        return true;
    }

    struct Node *right = node->pnext;
    struct Node *left = node->pprevious;
    left->pnext = right;
    right->pprevious = left;
    node->pnext = NULL;
    node->pprevious = NULL;

    update_length(LENGTH_DELETE);

    printf("~~~~~ Deleted %d.\n", node->data);
    return true;
}

void
print_list()
{
    if (HEAD == NULL || TAIL == NULL) {
        LOG_ERROR("Linked list is not initialised.");
        return;
    }
    struct Node *current_node = HEAD;
    printf("~~~~~ Linked list: [");
    while (current_node->pnext != NULL) {
        printf("%d, ", current_node->data);
        current_node = current_node->pnext;
        if (current_node == TAIL) {
            printf("%d", current_node->data);
            break;
        }
    }
    printf("]\n");
    return;
}

int
main(int argc, char *argv[])
{
    bool insertion_success;

    struct Node node_a = create_node(5);
    HEAD = &node_a;
    TAIL = &node_a;
    printf("~~~~~ Inserted %d.\n", node_a.data);

    struct Node node_b = create_node(7);
    insertion_success = insert_at(&node_b, 1);
    if (!insertion_success) {
        printf("~~~~~ [ERROR] Failed to insert %d", node_b.data);
    }

    struct Node node_c = create_node(9);
    insertion_success = append(&node_c);
    if (!insertion_success) {
        printf("~~~~~ [ERROR] Failed to insert %d", node_c.data);
    }


    struct Node node_d = create_node(17);
    insertion_success = insert_at(&node_d, 1);
    if (!insertion_success) {
        printf("~~~~~ [ERROR] Failed to insert %d", node_d.data);
    }

    struct Node node_e = create_node(23);
    insertion_success = insert_at(&node_e, 1);
    if (!insertion_success) {
        printf("~~~~~ [ERROR] Failed to insert %d", node_e.data);
    }

    print_list();

    bool deletion_success = delete_node(&node_b);
    if (deletion_success) {
        print_list();
    }

    printf("~~~~~ List length: %d.\n", LENGTH);
    printf("~~~~~ HEAD = %d.\n", HEAD->data);
    printf("~~~~~ TAIL = %d.\n", TAIL->data);

    return 0;
}
