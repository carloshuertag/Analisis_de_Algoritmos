#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <obstack.h>

#define obstack_chunk_alloc xmalloc
#define obstack_chunk_free free
#define THREADCOUNT 4

void *xmalloc(size_t size)
{
    void *value = malloc(size);
    if (value == 0)
        fatal("virtual memory exhausted");
    return value;
}

/* obstack section */
struct obstack threadObstack[THREADCOUNT];

/* type definition section */
typedef struct ParTreeST
{
    struct ParTreeST *left;
    struct ParTreeST *right;
    int key;
    int count;
} ParTree;

typedef struct ParNodesLinkST
{
    struct ParNodesLinkST *next;
    struct ParTreeST *node;
} ParNodesLink;

/* static or ordinary global variable definition section. */
static ParTree *root = (void *)0;
static ParNodesLink *head[THREADCOUNT];
static pthread_mutex_t mutex[THREADCOUNT];

void tree_initialize()
{
    int ii;
    for (ii = 0; ii < THREADCOUNT; ii++)
    {
        pthread_mutex_init(mutex + ii, (void *)0);
        head[ii] = (ParNodesLink *)0;
    }
    return;
}

void initObstack(int count)
{
    int ii;
    for (ii = 0; ii < count; ii++)
    {
        obstack_init(threadObstack + ii);
        obstack_chunk_size(threadObstack + ii) = 1024 * 1024;
    }
}

void treeInsertPar(ParTree *v, int len, int threadid)
{
    ParTree *ptr, *y;
    for (ptr = root, y = (ParTree *)0;;)
    {
        if (ptr == (void *)0)
        {
            pthread_mutex_t *mutexPtr = mutex +
                                        (int)((((unsigned long long)y) /
                                        sizeof(ParTree)) % THREADCOUNT);
            pthread_mutex_lock(mutexPtr);
            if (y == (void *)0) /* empty tree */
            {
                if (root != (void *)0) /* still empty */
                {
                    root = v;
                    pthread_mutex_unlock(mutexPtr);
                    addLinkedNode(v, threadid);
                    return;
                }
                else /* not empty anymore */
                {
                    pthread_mutex_unlock(mutexPtr);
                    ptr = root;
                }
            }
            else if (v->key < y->key) /* left child */
            {
                if (y->left == (void *)0) /* add a new node here */
                {
                    y->left = v;
                    pthread_mutex_unlock(mutexPtr);
                    addLinkedNode(v, threadid);
                    return;
                }
                else /*	occupied */
                {
                    ptr = y->left;
                    pthread_mutex_unlock(mutexPtr);
                }
            }
            else /* right child	*/
            {
                if (y->right == (void *)0) /* add a new node here */
                {
                    y->right = v;
                    pthread_mutex_unlock(mutexPtr);
                    addLinkedNode(v, threadid);
                    return;
                }
                else /*	occupied */
                {
                    ptr = y->right;
                    pthread_mutex_unlock(mutexPtr);
                }
            }
        }
        y = ptr;
        if (v->key == ptr->key) /* already in the tree */
        {
            /* need to lock this node before increasing its count	*/
            pthread_mutex_t *mutexPtr = mutex +
                                        (int)((((unsigned long long)ptr) /
                                        sizeof(ParTree)) % THREADCOUNT);
            pthread_mutex_lock(mutexPtr);
            ptr->count++;
            pthread_mutex_unlock(mutexPtr);
            return;
        }
        if (v->key < ptr->key)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    }
}

void addLinkedNode(ParTree *v, int threadid)
{
    ParNodesLink *ptr;
    ptr = (ParNodesLink *)obstack_alloc(threadObstack + threadid,
                                        sizeof(ParNodesLink));
    ptr->node = v;
    ptr->next = head[threadid];
    head[threadid] = ptr;
}

ParTree *treeParSearch(int key, int len)
{
    ParTree *ptr;
    int flag;
    for (ptr = root; ptr != (void *)0;)
        if (key == ptr->key)
            return ptr;
        else if (key < ptr->key)
            ptr = ptr->left;
        else
            ptr = ptr->right;
    return ptr;
}

void linkListScanPar(int threadid)
{
    ParNodesLink *ptr;
    for (ptr = head[threadid]; ptr != (void *)0; ptr = ptr->next)
        printf("Node linked to value[% s][% d]\n", ptr->node->key,
                ptr->node->count);
}

/* all the obstacks will be in an “uninitialized” state after the cleanup. */
void cleanUp(int count)
{
    int ii;
    for (ii = 0; ii < count; ii++)
        obstack_free(threadObstack + ii, (void *)0);
}

int main(){
    
    return 0;
}