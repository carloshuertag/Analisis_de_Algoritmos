#include <stdio.h>
#include <stdlib.h>

/** 
 *  Node struct definition for binary tree nodes
 *  key: node's item
 *  count: key frequency count
 *  left: left child node
 *  right: right child node
*/
typedef struct Node
{
    int key, count;
    struct Node *left, *right;
} * Node;

/**
 *  creates a new binary tree node with given nodes, entry n count.
 *  @param item binary tree node entry.
 *  @param cnt binary tree node count.
 *  @param lft binary tree left node.
 *  @param rght binary tree right node.
 *  @return new binary tree node.
*/
Node createNode(int item, int cnt, Node lft, Node rght)
{
    Node node = (Node)malloc(sizeof(struct Node));
    if (!node)
    {
        perror("Error: Node memory allocation failed");
        exit(1);
    }
    if (lft == NULL && rght == NULL)
        node->count = cnt;
    else
        node->count = lft->count + rght->count;
    node->key = item;
    node->left = lft;
    node->right = rght;
    return node;
}

/**
 *  MinHeap struct definition for min-heap
 *  arr: heap array
 *  size: size of heap array
 *  capacity: heap array max length
*/
typedef struct MinHeap {
    Node* arr;
    int size;
    int capacity;
} MinHeap;

// Get the index of the parent
int parent(int i) { return (i - 1) / 2; }

int leftChild(int i) { return (2*i + 1); }

int rightChild(int i) { return (2*i + 2); }

// Return the root node element,
    // since that's the minimum
Node getMin(MinHeap* heap) { return heap->arr[0]; }

MinHeap* createMinHeap(unsigned int capacity)
{
    MinHeap* minheap = (MinHeap*) malloc(sizeof(MinHeap));
    minheap->arr = (Node*) calloc(capacity, sizeof(struct Node));
    minheap->capacity = capacity;
    minheap->size = 0;
    return minheap;
}

// Inserts an element to the min heap
    // We first add it to the bottom (last level)
    // of the tree, and keep swapping with it's parent
    // if it is lesser than it. We keep doing that until
    // we reach the root node. So, we will have inserted the
    // element in it's proper position to preserve the min heap property
MinHeap* insert2MinHeap(MinHeap* heap, Node element)
{
    if (heap->size == heap->capacity) {
        perror("Couldn't insert node, heap is full.");
        return heap;
    }
    heap->size++;
    heap->arr[heap->size - 1] = element; //add element to end
    int curr = heap->size - 1; // swap until the root is reached
    while (curr > 0 && heap->arr[parent(curr)]->count > heap->arr[curr]->count) {
        Node temp = heap->arr[parent(curr)];
        heap->arr[parent(curr)] = heap->arr[curr];
        heap->arr[curr] = temp;
        curr = parent(curr); // update the current index of element
    }
    return heap; 
}

// Rearranges the heap as to maintain
// the min-heap property
MinHeap* heapify(MinHeap* heap, int index) {
    if (heap->size <= 1)
        return heap;
    int left = leftChild(index); 
    int right = rightChild(index); 
    int smallest = index;
    if (left < heap->size && heap->arr[left]->count < heap->arr[index]->count) 
        smallest = left; // update smallest to the left child
    if (right < heap->size && heap->arr[right]->count < heap->arr[smallest]->count) 
        smallest = right; // update smallest to the right child,
    //guarantees smallest from the subtree
    if (smallest != index) //until the root is reached
    { // swap smallest with current element
        Node temp = heap->arr[index];
        heap->arr[index] = heap->arr[smallest];
        heap->arr[smallest] = temp;
        heap = heapify(heap, smallest); 
    }
    return heap;
}

// Deletes the minimum element, at the root
MinHeap* deleteMin(MinHeap* heap) {
    if (!heap || heap->size == 0)
        return heap;
    int size = heap->size;
    Node last_element = heap->arr[size-1];
    heap->arr[0] = last_element; // update root value with the last element
    heap->size--; size--; // remove the last element
    heap = heapify(heap, 0); // mantain min-heap property
    return heap;
}

// Deletes an element, indexed by index
MinHeap* deleteElement(MinHeap* heap, int index) {
    heap->arr[index] = getMin(heap);
    heap->arr[index]->count--;// indexed element is the lowest
    // Now keep swapping, until we update the tree
    int curr = index;
    while (curr > 0 && heap->arr[parent(curr)]->count > heap->arr[curr]->count) {
        Node temp = heap->arr[parent(curr)];
        heap->arr[parent(curr)] = heap->arr[curr];
        heap->arr[curr] = temp;
        curr = parent(curr);
    }
    heap = deleteMin(heap);
    return heap;
}

// prints heap in an inorder traversal
void printMinHeap(MinHeap* heap) {
    printf("Min Heap:\n");
    for (int i=0; i<heap->size; i++) {
        printf("%d -> ", heap->arr[i]->count);
    }
    printf("\n");
}

void freeMinHeap(MinHeap* heap) {
    if (!heap)
        return;
    free(heap->arr);
    free(heap);
}

int main() {
    // Capacity of 10 elements
    MinHeap* heap = createMinHeap(4);
    Node node1 = createNode(23, 1, NULL, NULL);
    Node node2 = createNode(21, 2, NULL, NULL);
    Node node3 = createNode(22, 2, NULL, NULL);
    Node node4 = createNode(20, 4, NULL, NULL);
    insert2MinHeap(heap, node3);
    insert2MinHeap(heap, node4);
    insert2MinHeap(heap, node1);
    insert2MinHeap(heap, node2);
    printMinHeap(heap);
    while(heap->size > 1)
    {
        Node aux1 = getMin(heap);
        deleteMin(heap);
        Node aux2 = getMin(heap);
        deleteMin(heap);
        insert2MinHeap(heap, createNode(257, -1, aux1, aux2));
    }
    printMinHeap(heap);
    // Delete the heap->arr[1] (50)
    //delete_element(heap, 1);
    //deleteMin(heap);
    //printMinHeap(heap);
    freeMinHeap(heap);
    return 0;
}