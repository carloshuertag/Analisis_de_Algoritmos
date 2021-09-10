/** 
 *  binary search tree node struct.
*/
typedef struct Node
{
    Entry key;
    struct Node *l, *r;
} * Node;

/** 
 *  empty binary search tree node.
 *  @return a null pointer to binary search tree node.
*/
Node emptyBst() { return NULL; }

/**
 *  creates a new binary search tree node with given nodes and a given entry.
 *  @param item binary search tree node entry.
 *  @param a binary search tree left node.
 *  @param b binary search tree right node.
 *  @return new binary search tree node.
*/
Node createBst(Entry item, Node a, Node b)
{
    Node t = (Node)malloc(sizeof(struct Node));
    t->key = item;
    t->l = a;
    t->r = b;
    return t;
}

/**
 *  given binary search tree node is empty.
 *  @param a binary search tree node.
 *  @return whether the node is empty.
*/
bool isEmptyBst(Node a) { return a == NULL; }

/**
 *  given binary search tree node key.
 *  @param a binary search tree node.
 *  @return binary search tree node key.
*/
Entry key(Node a) { return a->key; }

/**
 *  given binary search tree node left leaf.
 *  @param a binary search tree node.
 *  @return binary search tree node left leaf.
*/
Node left(Node a) { return a->l; }

/**
 *  given binary search tree node right leaf.
 *  @param a binary search tree node.
 *  @return binary search tree node right leaf.
*/
Node right(Node a) { return a->r; }

// returns a binary search tree node weight
/**
 *  given binary search tree node weight.
 *  @param a binary search tree node.
 *  @return binary search tree node weight.
*/
int weight(Node a)
{
    if (isEmptyBst(a))
        return 0;
    return weight(left(a)) + weight(right(a)) + 1;
}

/**
 *  prints given binary search tree node in preorder.
 *  @param a binary search tree node.
*/
void printPreOrder(Node a)
{
    if (!isEmptyBst(a))
    {
        printEntry(key(a));
        printPreOrder(right(a));
        printPreOrder(left(a));
    }
}

/**
 *  prints given binary search tree node in inorder.
 *  @param a binary search tree node.
*/
void printInOrder(Node a)
{
    if (!isEmptyBst(a))
    {
        printInOrder(left(a));
        printEntry(key(a));
        printInOrder(right(a));
    }
}

/**
 *  prints given binary search tree node in postorder.
 *  @param a binary search tree node.
*/
void printPostOrder(Node a)
{
    if (!isEmptyBst(a))
    {
        printPostOrder(left(a));
        printPostOrder(right(a));
        printEntry(key(a));
    }
}

/**
 *  inserts a new binary search tree node with given key and parent node.
 *  @param item binary search tree node entry.
 *  @param a binary search tree node.
 *  @return new binary search tree node.
*/
Node insertNode(Entry item, Node a)
{
    if (isEmptyBst(a))
        return createBst(item, emptyBst(), emptyBst());
    if (isEntryLower(key(a), item))
        return createBst(key(a), insertNode(item, left(a)), right(a));
    if (isEntryGreater(key(a), item))
        return createBst(key(a), left(a), insertNode(item, right(a)));
    return NULL;
}