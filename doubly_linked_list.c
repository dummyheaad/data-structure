#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct dllist 
{
	int val;
	struct dllist* prev;
	struct dllist* next;
};

typedef struct dllist dllnode;

dllnode* create(int val)
{
    dllnode* node = (dllnode*) malloc(sizeof(dllnode));
    if (node == NULL)
        return NULL;
    node->val = val;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

dllnode* insert(dllnode* head, int val)
{
    dllnode* node = (dllnode*) malloc(sizeof(dllnode));
    if (node == NULL)
        return NULL;
    node->val = val;
    node->prev = NULL;
    node->next = head;
    head->prev = node;
    head = node;
    return head;
}

bool find(dllnode* traversal, int val)
{
    if (traversal->val == val)
        return true;
    if (traversal->next == NULL)
        return false;
    find(traversal->next, val);
}

void destroy(dllnode** head, dllnode* traversal, dllnode* target)
{
	// hapus elemen awal (head)
    if (traversal == target && traversal->prev == NULL)
    {
        *head = traversal->next;
        (*head)->prev = NULL;
        free(target);
        return;
    }

    // hapus elemen akhir (tail)
    if (traversal == target && traversal->next == NULL)
    {
        dllnode* before = traversal->prev;
        before->next = NULL;
        free(target);
        return;
    }

    // hapus elemen tengah (middle)
    if (traversal == target)
    {
        dllnode* before = traversal->prev;
        dllnode* after = traversal->next;
        before->next = after;
        after->prev = before;
        free(target);
        return;
    }
    destroy(head, traversal->next, target);
}

void destroyAll(dllnode* head)
{
	if (head->next == NULL)
		return;
	destroyAll(head->next);
	free(head->next);
	return;
}

void display(dllnode* head)
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

int main(void)
{
    // create new doubly linked lists
    dllnode* node_baru = create(27);
    
    // insert some new node
    node_baru = insert(node_baru, 30);
    node_baru = insert(node_baru, 72);
    node_baru = insert(node_baru, 99);
    
    // print all nodes before deletion
    display(node_baru);
    puts("");
    puts("");
    
    // find node whose value is 30
    bool check = find(node_baru, 30);
    if (check)
        printf("30 is found!!");
    else
        printf("30 is not found");
    puts("");
    
    // destroy head node
    destroy(&node_baru, node_baru, node_baru);
    check = find(node_baru, 99);
    if (check)
        printf("99 is found!!");
    else
        printf("99 is not found");
    puts("");
    
    // destroy tail node
    destroy(&node_baru, node_baru, node_baru->next->next); 
    check = find(node_baru, 27);
    if (check)
        printf("27 is found!!");
    else
        printf("27 is not found");
    puts("");
    puts("");
    
    display(node_baru);
    destroyAll(node_baru);
    puts("");
    
    return 0;
}
