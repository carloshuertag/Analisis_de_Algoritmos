#define NOITEM 257
#define NOCOUNT 0

/** 
 *  Node struct definition for Huffman binary tree nodes
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
 *  creates a new Huffman tree node with given nodes, entry n count.
 *  if rght and lft are not null, merges both into returned node.
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
}

/**
 *  MinHeap struct definition for min-heap of Huffman tree nodes
 *  arr: heap array of Huffman tree nodes
 *  size: size of heap array
 *  capacity: heap array max length
*/
typedef struct MinHeap {
    Node* arr;
    int size;
    int capacity;
} MinHeap;

/** 
 *  gets the index of a node's parent
 *  @param i index of a node
 *  @return node's parent index
*/
int parent(int i) { return (i - 1) / 2; }

/**
 *  gets the index of node's left child
 *  @param i index of a node
 *  @return node's left child index
*/
int leftChild(int i) { return (2*i + 1); }

/**
 *  gets the index of node's right child
 *  @param i index of a node
 *  @return node's right child index
*/
int rightChild(int i) { return (2*i + 2); }

/**
 *  gets the minimum element from given heap
 *  @param heap given heap
*/
Node getMin(MinHeap* heap) { return heap->arr[0]; }

/**
 *  creates a Huffman tree nodes min heap
 *  @param capacity maximum capacity of heap
 *  @return created heap with given capacity
*/
MinHeap* createMinHeap(unsigned int capacity)
{
    MinHeap* minheap = (MinHeap*) malloc(sizeof(MinHeap));
    if (!minheap)
    {
        perror("Error: minheap memory allocation failed");
        exit(1);
    }
    minheap->arr = (Node*) calloc(capacity, sizeof(struct Node));
    if (!minheap->arr)
    {
        perror("Error: arr memory allocation failed");
        exit(1);
    }
    minheap->capacity = capacity;
    minheap->size = 0;
    return minheap;
}

/**
 *  inserts given element into the given heap
 *  @param heap given heap
 *  @return updated given heap
*/
MinHeap* insert2MinHeap(MinHeap* heap, Node element)
{
    if (heap->size == heap->capacity) {
        perror("Couldn't insert node, heap is full");
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

/**
 *  rearranges the min heap as to maintain the min-heap property
 *  starting from given index
 *  @param heap given heap
 *  @param index given index
 *  @return updated heap ensuring min-heap property
*/
MinHeap* heapify(MinHeap* heap, int index)
{
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

/**
 *  deletes the minimum element in given heap
 *  @param heap given heap
 *  @return updated given heap
*/
MinHeap* deleteMin(MinHeap* heap) {
    if (!heap || heap->size == 0)
        return heap;
    int size = heap->size;
    Node lastElement = heap->arr[size-1];
    heap->arr[0] = lastElement; // update root value with the last element
    heap->size--; size--; // remove the last element
    heap = heapify(heap, 0); // mantain min-heap property
    return heap;
}


// prints heap in an inorder traversal
void printMinHeap(MinHeap* heap) {
    for (int i=0; i<heap->size; i++) {
        printf("%d -> ", heap->arr[i]->count);
    }
    printf("\n");
}
/**
 *  frees min heap memory: its fields and array
 *  @param heap given heap
*/
void freeMinHeap(MinHeap* heap) {
    if (!heap)
        return;
    free(heap->arr);
    free(heap);
}

/**
 *  creates the binary tree to Huffman code a file, with a given frequency table.
 *  @param arr nx2 dimensions array in which elements are definied.
 *  like this: arr[x][0] for the element and its frequenct arr[x][1]
 *  @param n dimension of the array of the 2 dimensions array.
 *  @return binary tree root in which is built the tree to Hufman code.
*/
Node createTree(unsigned int arr[][2], int n)
{
    MinHeap* heap = createMinHeap(n);
    int i;
    for (i = 0; i < n; i++)
    { // initilializing heap with items and frequencies from given table
        insert2MinHeap(heap, createNode(arr[i][0], arr[i][1], NULL, NULL));
    }
    printMinHeap(heap);
    Node firstLowest, secondLowest;
    while(heap->size > 1)
    {
        firstLowest = getMin(heap);
        heap = deleteMin(heap);
        secondLowest = getMin(heap);
        heap = deleteMin(heap);
        // inserts a new node in which the lowest two nodes will be merged
        insert2MinHeap(heap, createNode(NOITEM, NOCOUNT, firstLowest, secondLowest));
    }
    firstLowest = getMin(heap); // built Huffman tree in its root
    printMinHeap(heap);
    freeMinHeap(heap);
    return firstLowest;
}
