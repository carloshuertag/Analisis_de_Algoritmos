#define NOITEM 257
#define NOCOUNT 0

/** 
 *  Node struct definition for Huffman binary tree nodes
 *  byte: node's item
 *  count: byte frequency count
 *  left: left child node
 *  right: right child node
*/
typedef struct Node
{
    unsigned short byte;
    unsigned int count;
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
Node createNode(unsigned short item, unsigned int cnt, Node lft, Node rght)
{
    Node node = (Node)malloc(sizeof(struct Node));
    if (!node)
    { // error allocating memory
        perror("Error: Node memory allocation failed");
        exit(1);
    }
    node->byte = item;
    if (lft == NULL && rght == NULL)
        node->count = cnt; // leaf with given count
    else // merge two subtrees
        node->count = lft->count + rght->count;
    node->left = lft;
    node->right = rght;
}

/**
 *  frees the memory allocated for a binary tree.
 *  @param node binary tree root.
*/
void freeTree(Node root)
{
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/**
 *  MinHeap struct definition for min-heap of Huffman tree nodes
 *  arr: heap array of Huffman tree nodes
 *  size: size of heap array
 *  capacity: heap array max length
*/
typedef struct MinHeap
{
    Node* arr;
    unsigned int size;
    unsigned int capacity;
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
    { // error allocating memory
        perror("Error: minheap memory allocation failed");
        exit(1);
    }
    minheap->arr = (Node*) calloc(capacity, 
                                    sizeof(struct Node));
    if (!minheap->arr)
    { // error allocating memory
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
    if (heap->size == heap->capacity)
    {
        perror("Couldn't insert node, heap is full.\n");
        return heap;
    }
    heap->size++;
    int current = heap->size - 1;
    heap->arr[current] = element; //add element to end
    // swap until the root is reached
    while (current != 0 &&
            heap->arr[parent(current)]->count > heap->arr[current]->count)
    {
        Node temp = heap->arr[parent(current)];
        heap->arr[parent(current)] = heap->arr[current];
        heap->arr[current] = temp;
        current = parent(current); // update the current index
    }
    return heap; 
}

/**
 *  rearranges the min heap to maintain the min-heap property
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
    if (left < heap->size
        && heap->arr[left]->count < heap->arr[index]->count) 
        smallest = left; // update smallest to the left child
    if (right < heap->size
        && heap->arr[right]->count < heap->arr[smallest]->count) 
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
MinHeap* deleteMin(MinHeap* heap)
{
    if (!heap || heap->size == 0)
        return heap;
    int size = heap->size;
    Node lastElement = heap->arr[size-1];
    heap->arr[0] = lastElement; // update root with the last element
    heap->size--; size--; // remove the last element
    heap = heapify(heap, 0); // mantain min-heap property
    return heap;
}

/**
 *  frees min heap memory: its fields and array
 *  @param heap given heap
*/
void freeMinHeap(MinHeap* heap)
{
    if (!heap)
        return;
    free(heap->arr);
    free(heap);
}

/**
 *  builds the Huffman binary tree, with a given frequency table.
 *  @param arr nx2 dimensions array in which elements are definied.
 *  like this: arr[x][0] for the element and its frequenct arr[x][1]
 *  @param n dimension of the array of the 2 dimensions array.
 *  @return binary tree root in which the Huffman tree is built.
*/
Node buildTree(unsigned int arr[][2], unsigned int n)
{
    MinHeap* heap = createMinHeap(n); // create min heap
    int i;
    for (i = 0; i < n; i++) // init muin heap with frequencies table
        insert2MinHeap(heap, createNode(arr[i][0], arr[i][1],
                                        NULL, NULL));
    Node leftToMerge, rightToMerge;
    while(heap->size > 1)
    { // merge two smallest nodes
        leftToMerge = getMin(heap); // get the smallest node
        heap = deleteMin(heap);
        rightToMerge = getMin(heap); // get the next smallest node
        heap = deleteMin(heap); // inserts the 2 smallest nodes merged
        insert2MinHeap(heap, createNode(NOITEM, NOCOUNT,
                                leftToMerge, rightToMerge));
    }
    leftToMerge = getMin(heap); // built Huffman tree at min heap root
    freeMinHeap(heap);
    return leftToMerge; // return root of Huffman tree
}
