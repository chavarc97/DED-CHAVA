#include <stdio.h>
#include <stdlib.h>

// Structs
typedef struct node
{
    int value;
    struct node *next;
    struct node *prev;
} node;

node *header = NULL; //<--- esta es nuestra primer lista ligada! :)

// prototypes
void print_list(node *h);
node *newNode(int n);
void add(node *n);
int insert_after(node *h, int n);
int insert_before(node *h, int n);
void delete(int n_val);
void search(int n);

int main()
{
    header = newNode(1);

    // INITIALIZE THE LINKED LIST
    for (int i = 1; i < 5; i++)
    {
        node *n = newNode(i + 1);
        add(n);
    }

    // menu variables--------------
    int selection;
    int todel = 0;
    int toinsert = 0, tosearch = 0;
    int putafter = 0, putbefore = 0;
    node *new_node = NULL;
    int r = 0;
    // ---------------------------
    while (1)
    {
        print_list(header);
        printf("Select option:\n 1) delete\n 2) insert after\n 3)insert before\n"
               " 4) search\n 5)print\n");
        printf("\topc:");
        r = scanf("%d", &selection);
        switch (selection)
        {
        case 1:
            printf("\tnumber to delete: ");
            r = scanf("%d", &todel);
            getchar();
            delete (todel);
            break;
        case 2:
            printf("\tnumber to insert: ");
            r = scanf("%d", &toinsert);
            getchar();
            printf("\tinsert after which node?: ");
            r = scanf("%d", &putafter);

            new_node = newNode(toinsert);
            if (!insert_after(new_node, putafter)) // == 0
            {
                // fail to insert, we need to free node
                printf("Failed to insert\n");
                free(new_node);
            }
            break;
        case 3:
            printf("\tnumber to insert: ");
            r = scanf("%d", &toinsert);
            getchar();
            printf("\tinsert after which node?: ");
            r = scanf("%d", &putbefore);

            new_node = newNode(toinsert);
            if (!insert_before(new_node, putbefore))
            {
                // fail to insert, we need to free node
                printf("Failed to insert\n");
                free(new_node);
            }
            break;
        case 4:
            printf("\tnumber to search: ");
            r = scanf("%d", &tosearch);
            getchar();
            search(tosearch);
            break;
        case 5:
            print_list(header);
            break;
        }
    }
}

// FUNCTIONS --------------------------------->

void print_list(node *h)
{
    /*
    The key points in this implementation are:
        * We traverse the list twice, once forward and once backward.
        * We keep track of the last node during the forward traversal to start
          our backward traversal.
     */
    node *tmp = header;
    node *last = NULL; // last pointer
    if (header == NULL)
        printf("NO DATA FOUND!");

    while (tmp != NULL)
    {
        /* code */
        printf("%d -> ", tmp->value);
        last = tmp; // save the last node address that is not null
        tmp = tmp->next;
    }
    // Once the first loop is finish we star printing the nodes backwards
    // now tmp will be equal to las to avoid using a null node pointer since we used last to
    tmp = last->prev;
    while (tmp != NULL)
    {
        printf("%d -> ", tmp->value);
        if (tmp->prev == NULL)
            printf("[NULL]");
        tmp = tmp->prev;
    }
    printf("\n");
}

node *newNode(int n)
{
    node *n_node = (node *)malloc(sizeof(node));
    n_node->next = NULL; // meanwhile assign null.
    n_node->value = n;   // assign the value oof the node.
    n_node->prev = NULL; // assign NULL to the prev direction on the head.
    return n_node;
}

void add(node *n)
{
    node *tmp = header;
    node *new = n;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = n;
    new->prev = tmp;
}

int insert_after(node *n, int node_val)
{
    if (header == NULL)
    {
        return 0; // List is empty
    }
    // Start from the header
    node *curr = header;

    // Traverse the list to find the node with the value node_val
    while (curr != NULL)
    {
        if (curr->value == node_val)
        {
            // Insert the new node after the current node
            n->next = curr->next; // n->next points to the next node of the current node
            curr->next = n;       // current node points to the new node
            n->prev = curr;       // new node points to the current node
            if (n->next != NULL)
            {
                n->next->prev = n; // the next node of the new node points to the new node
            }
            return 1; // Insertion successful
        }
        curr = curr->next;
    }
    // If the node with node_val is not found, return 0
    return 0;
}

int insert_before(node *n, int val)
{
    node *tmp = header;
    node *prev = NULL;
    // special case: insert before header
    if (header->value == val)
    {
        header->prev = n;
        n->next = header;
        header = n; // Update the header pointer to the new node
        return 1;
    }
    // traverse the list to find the node with the value val
    while (tmp != NULL)
    {
        // Find the node with the provided value
        if (tmp->value == val)
        {
            prev->next = n; // the previous node points to the new node
            n->prev = prev; // the new node prev points to the previous node
            n->next = tmp;  // the new node next points to the current node
            tmp->prev = n;  // the current node prev points to the new node to complete the insertion
            return 1;
        }
        // move to the next node
        prev = tmp; // keep track of the prev node
        tmp = tmp->next;
    }
    // node not found
    return 0;
}

void delete(int n_val)
{
    node *n_ptr = header;
    node *prev = NULL;

    // Special case if the node to delete is the first
    if (header->value == n_val)
    {
        header = header->next; // update the header to the next node
        header->prev = NULL;   // update the prev pointer of the new header to NULL
        free(n_ptr);           // free n_ptr who is pointing to the header node
        return;
    }
    // Traverse the list to find the node to delete
    while (n_ptr != NULL)
    {
        if (n_ptr->value == n_val)
        {
            prev->next = n_ptr->next;
            if (prev->next != NULL)
            {
                prev->next->prev = prev;
            }
            free(n_ptr);
            return;
        }
        prev = n_ptr;
        n_ptr = n_ptr->next;
    }
    // Node not found
    printf("Value not found\n");
    return;
}

void search(int n)
{
    node *n_ptr = header;
    while (n_ptr != NULL)
    {
        if (n_ptr->value == n)
        {
            if (n_ptr->prev == NULL)
                printf(" NULL ");
            else
                printf(" [ %p | %d] ", &n_ptr->prev, n_ptr->prev->value);
                 
            printf("<--> \033[1;32m[ %p | %d]\033[0m <-->", &n_ptr, n_ptr->value);

            if (n_ptr->next == NULL)
                printf("NULL");
            else
                printf(" [ %p | %d] ", &n_ptr->next, n_ptr->next->value);
            getchar();
            return;
        }
        // move to the next node
        n_ptr = n_ptr->next;
    }
}
