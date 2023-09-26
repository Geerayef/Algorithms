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

bool
update_length(int operation)
{
    if (operation == LENGTH_INSERT) {
        LENGTH++;
        return true;
    }

    if (operation == LENGTH_DELETE) {
        LENGTH--;
        return true;
    }

    return false;
}

int
get_length()
{
    return LENGTH;
}

struct Node
create_node(int data)
{
    struct Node temp;
    temp.data = data;
    temp.pnext = NULL;
    temp.pprevious = NULL;

    return temp;
}

bool
prepend(struct Node *node)
{
    if (HEAD == NULL || TAIL == NULL) {
        LOG_ERROR("Linked list is not initialised.");
        return false;
    }

    if (node == NULL) {
        LOG_ERROR("Null pointer: The given pointer to the element to prepend is null.");
        return false;
    }

    HEAD->pprevious = node;
    node->pnext = HEAD;
    node->pprevious = NULL;
    HEAD = node;

    update_length(LENGTH_INSERT);

    printf("~~~~~ Prepended %d to the list.\n", node->data);
    return true;
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

    TAIL->pnext = node;
    node->pprevious = TAIL;
    node->pnext = NULL;
    TAIL = node;

    update_length(LENGTH_INSERT);

    printf("~~~~~ Appended %d to the list.\n", node->data);
    return true;
}

/* args:
 *      struct Node *node   - pointer to the new node which is to be inserted into the list.
 *      int position        - 0-indexed value that indicates where in the list to insert the given node.
 * */
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

    if (position < 0) {
        LOG_ERROR("Index out of bounds: The given position, to insert new element at,\
                is negative.");
        return false;
    }

    if (position == 0) {
        bool prepend_success = prepend(node);
        if (prepend_success) {
            return true;
        }
    }

    if (position == LENGTH) {
        bool append_success = append(node);
        if (append_success) {
            return true;
        }
        return false;
    }

    struct Node *current_node = HEAD;
    int i = 0;
    while (i < position) {
        if (current_node->pnext == NULL) {
            break;
        }
        i++;
        current_node = current_node->pnext;
    }

    if (i < position) {
        LOG_ERROR("Index out of bounds. This should not happen! Length count might be incorrect\
                , or memory might be corrupted and pointers might be lost.");
        return false;
    } 

    if (i == position) {
        struct Node* left = current_node->pprevious;
        left->pnext = node;
        node->pprevious = left;
        current_node->pprevious = node;
        node->pnext = current_node;
        update_length(LENGTH_INSERT);
    }

    printf("~~~~~ Inserted %d at position %d.\n", node->data, position);
    return true;
}

bool
delete_node(struct Node *node)
{
    if (HEAD == NULL || TAIL == NULL) {
        LOG_ERROR("Linked list is not initialised.");
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

/* args:
 *      int position - 0-indexed value that indicates the position in the list from which to retrieve the element.
 * */
bool
delete_at(int position)
{
    if (HEAD == NULL || TAIL == NULL) {
        LOG_ERROR("Linked list is not initialised.")    ;
        return false;
    }

    if (position > LENGTH) {
        LOG_ERROR("Index out of bounds: The given position, to delete an element from,\
                is bigger than the length of the linked list.");
        return false;
    }

    struct Node *current_node = HEAD;
    int i = 0;
    while (i < position) {
        if (current_node->pnext == NULL) {
            return false;
        }
        i++;
        current_node = current_node->pnext;
    }

    struct Node *right = current_node->pnext;
    struct Node *left = current_node->pprevious;
    left->pnext = right;
    right->pprevious = left;
    current_node->pnext = NULL;
    current_node->pprevious = NULL;

    update_length(LENGTH_DELETE);

    printf("~~~~~ Deleted %d.\n", current_node->data);
    return true;
}

/* args:
 *      int position - 0-indexed value that indicates the position in the list from which to retrieve the element.
 * */
struct Node *
get_node_at(int position)
{
    if (HEAD == NULL || TAIL == NULL) {
        LOG_ERROR("Linked list is not initialised.");
        return NULL;
    }

    if (position >= LENGTH) {
        LOG_ERROR("Index out of bounds: The given position, to insert new element at,\
                is bigger than the length of the linked list.");
        return NULL;
    }

    if (position < 0) {
        LOG_ERROR("Index out of bounds: The given position, to insert new element at, is negative.");
        return NULL;
    }

    if (position == 0) {
        return HEAD;
    }

    if (position == LENGTH - 1) {
        return TAIL;
    }

    struct Node *current_node = HEAD;
    int i = 0;
    while (i < position) {
        if (current_node->pnext == NULL) {
            break;
        }
        i++;
        current_node = current_node->pnext;
    }

    if (i < position) {
        LOG_ERROR("Index out of bounds. This should not happen! Length count might be incorrect\
                , or memory might be corrupted and pointers might be lost.");
        return NULL;
    }

    if (i == position) {
        return current_node;
    }

    return NULL;
}

void
print_list_overview()
{
    printf("~~~~~ List length: %d.\n", LENGTH);
    printf("~~~~~ HEAD = %d.\n", HEAD->data);
    printf("~~~~~ TAIL = %d.\n", TAIL->data);

    return;
}

void
print_list_nodes()
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
    bool deletion_success;

    struct Node node_a = create_node(5);
    HEAD = &node_a;
    TAIL = &node_a;
    LENGTH = 1;
    printf("~~~~~ Initialised the list. First node: %d.\n", node_a.data);

    struct Node node_b = create_node(7);
    insertion_success = append(&node_b);
    if (!insertion_success) {
        printf("~~~~~ [ERROR] Failed to insert %d", node_b.data);
    }

    struct Node node_c = create_node(9);
    insertion_success = prepend(&node_c);
    if (!insertion_success) {
        printf("~~~~~ [ERROR] Failed to insert %d", node_c.data);
    }

    struct Node node_d = create_node(17);
    insertion_success = insert_at(&node_d, 1);
    if (!insertion_success) {
        printf("~~~~~ [ERROR] Failed to insert %d", node_d.data);
    }

    struct Node node_e = create_node(23);
    insertion_success = insert_at(&node_e, 0);
    if (!insertion_success) {
        printf("~~~~~ [ERROR] Failed to insert %d", node_e.data);
    }

    print_list_nodes();

    deletion_success = delete_node(&node_b);
    if (!deletion_success) {
        printf("~~~~~ [ERROR] Something went wrong while deleting specified node.\n");
    }

    deletion_success = delete_at(1);
    if (!deletion_success) {
        printf("~~~~~ [ERROR] Something went wrong while deleting node at given index.\n");
    }

    print_list_nodes();

    struct Node *needed_data;
    needed_data = get_node_at(2);
    if (needed_data == NULL) {
        printf("~~~~~ [ERROR] Tried to access an invalid list node.\n");
        return 0;
    }
    printf("~~~~~ Get data at position 2: %d\n", needed_data->data);

    print_list_overview();

    return 0;
}
