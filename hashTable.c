#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// hash function prototype
unsigned int hash(unsigned int x);

// node untuk linked-list
struct node {
    int val;
    struct node* next;
};

typedef struct node Node;

// fungsi untuk membuat satu buah node baru pada linked-list yang kosong
Node* createNode(int val)
{
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL)
        return NULL;
    new_node->val = val;
    new_node->next = NULL;
    return new_node;
}

// fungsi untuk insersi node via insert_begin
Node* insertNode(Node* head, int val)
{
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL)
        return NULL;
    new_node->val = val;
    new_node->next = head;
    head = new_node;
    return head;
}

// fungsi untuk mencari node dengan val tertentu secara rekursif
bool searchNode(Node* traversal, int val)
{
    if (traversal->val == val)
        return true;
    if (traversal->next == NULL)
        return false;
    return searchNode(traversal->next, val);
}

// fungsi untuk mencetak node pada satu node_list secara rekursif
void printNode(Node* traversal, bool check)
{
    int keep;
    if (check)
    {
        keep = traversal->val;    
        check = false;
    }

    if (traversal->next == NULL)
    {
        printf("%d->", traversal->val);
        return;
    }
    printNode(traversal->next, check);
    printf("%d", traversal->val);
    if (traversal->val != keep)
        printf("->");
}

// container untuk node_list
struct hash_table {
    Node** node_list;
};

typedef struct hash_table hashTable;

// fungsi untuk inisialisasi hash table
hashTable* init()
{
    hashTable* ht = (hashTable*) malloc(sizeof(hashTable));
    ht->node_list = (Node**) malloc(10 * sizeof(Node*));
    for (int i = 0;i < 10;i ++)
        ht->node_list[i] = (Node*) malloc(sizeof(Node));
    for (int i = 0;i < 10;i ++)
    {
        ht->node_list[i]->val = 0;
        ht->node_list[i]->next = NULL;
    }
    return ht;
}

// fungsi untuk insersi elemen ke dalam hash table
void insert(hashTable* ht, int val)
{
    int idx = hash(val);
    // kondisi pertama dimana belum ada elemen pada node_list di index tertentu
    if (ht->node_list[idx]->val == 0)
        ht->node_list[idx] = createNode(val);
    // kondisi kedua dimana telah terdapat elemen pada node_list di index tertentu
    // insersi elemen dilakukan via insert_begin
    else
        ht->node_list[idx] = insertNode(ht->node_list[idx], val);
    return;
}

// fungsi untuk mencari elemen dengan nilai tertentu pada hash table
bool search(hashTable* ht, int val, int* idx)
{
    bool check = false;
    for (int i = 0;i < 10;i ++)
    {
        check = searchNode(ht->node_list[i], val);
        if (check == true)
        {
            *idx = i;
            return check;
        }
    }
    return check;
}


// fungsi untuk menampilkan hash table
void display(hashTable* ht)
{
    puts("Hash Table");
    puts("==========");
    for (int i = 0;i < 10;i ++)
    {
        printf("[%d]\t", i);
        printNode(ht->node_list[i], true);
        puts("");
    }
    puts("=========");
    return;
}

// fungsi untuk menghancurkan hash table (dealokasi memori)
void destroy(hashTable* ht)
{
    puts("destroying the hash table...");
    for (int i = 0;i < 10;i ++)
        free(ht->node_list[i]);
    free(ht->node_list);
    free(ht);
    puts("the hash table has been destroyed...");
    return; 
}

// hash function
unsigned int hash(unsigned int x)
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x % 10;
}

int main() {
    hashTable* ht = init();
    // buat hashTable yang mengandung menyimpan nilai pada rentang 0 sampai 99
    for (int i = 0;i < 100;i ++)
        insert(ht, i);

    display(ht);

    // mencari nilai tertentu pada hash table
    bool isFound = false;
    int idx = -1;
    printf("Enter a value that you want to search: ");
    int n;
    scanf("%d", &n);
    isFound = search(ht, n, &idx);
    if (isFound)
        printf("The value %d is found at index: [%d]", n, idx);
    else
        printf("The value is not found....");
    puts("");

    // menghancurkan hash table
    destroy(ht);
    return 0;
}
