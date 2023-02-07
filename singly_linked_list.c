#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct sllist 
{
    int val;
    struct sllist* next;
};

typedef struct sllist sllnode;

sllnode* create(int val)
{
    sllnode* node = (sllnode*) malloc(sizeof(sllnode));
    if (node == NULL)
        return NULL;
    node->val = val;
    node->next = NULL;
    return node;
}

sllnode* insert(sllnode* head, int val)
{
    sllnode* node = (sllnode*) malloc(sizeof(sllnode));
    if (node == NULL)
        return NULL;
    node->val = val;
    node->next = head;
    head = node;
    return head;
}

bool find(sllnode* traversal, int val)
{
    if (traversal->val == val)
        return true;
    if (traversal->next == NULL)
        return false;
    find(traversal->next, val);
}

void display(sllnode* head)
{
    if (head->next == NULL)
    {
        puts("All element in the linked list:");
        printf("%d ", head->val);
        return;
    }
    display(head->next);
    printf("%d ", head->val);
}

void destroy(sllnode* head)
{
    if (head->next == NULL)
        return;
    destroy(head->next);
    free(head->next);
    return;
}

int main(void)
{
    // Create a new singly linked lists
    sllnode* new_node = create(27);
        
    if (new_node == NULL)
    {
        printf("Run out of memory...!!!");
        return 1;
    }
    
    // insert some new node
    new_node = insert(new_node, 30);
    new_node = insert(new_node, 45);
    new_node = insert(new_node, 70);
    new_node = insert(new_node, 100);
    
    // search for a node with a specific value
    printf("Enter the number that you want to search: ");
    int cari;
    scanf("%d", &cari);
    
    bool isFound = find(new_node, cari);
    (isFound) == true ? printf("%d is found !!!\n", cari) : printf("%d is not found !!!\n", cari);
    
    puts("");
    puts("");
    
    // print all of the node value in the linked lists
    display(new_node);
    
    destroy(new_node);
    return 0;
}
