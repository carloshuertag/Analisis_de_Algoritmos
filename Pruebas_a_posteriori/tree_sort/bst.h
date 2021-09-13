/** 
 *  binary search tree node struct.
*/
typedef struct Node
{
    Entry key;
    struct Node *left, *right;
} * Node;

/**
 *  creates a new binary search tree node with given nodes and a given entry.
 *  @param item binary search tree node entry.
 *  @param a binary search tree left node.
 *  @param b binary search tree right node.
 *  @return new binary search tree node.
*/
Node createBst(Entry item, Node lft, Node rght)
{
    Node t = (Node)malloc(sizeof(struct Node));
    t->key = item;
    t->left = lft;
    t->right = rght;
    return t;
}

/**
 *  given binary search tree node left leaf.
 *  @param a binary search tree node.
 *  @return binary search tree node left leaf.
*/
Node left(Node root) { return root->left; }

/**
 *  given binary search tree node right leaf.
 *  @param a binary search tree node.
 *  @return binary search tree node right leaf.
*/
Node right(Node root) { return root->right; }

// returns a binary search tree node weight
/**
 *  given binary search tree node weight.
 *  @param a binary search tree node.
 *  @return binary search tree node weight.
*/
int weight(Node root)
{
    if (root == NULL)
        return 0;
    return weight(left(root)) + weight(right(root)) + 1;
}

/**
 *  prints given binary search tree node in preorder.
 *  @param a binary search tree node.
*/
void printPreOrder(Node root)
{
    if (root != NULL)
    {
        printEntry(root->key);
        printPreOrder(right(root));
        printPreOrder(left(root));
    }
}

/**
 *  prints given binary search tree node in inorder.
 *  @param a binary search tree node.
*/
void printInOrder(Node root)
{
    if (root != NULL)
    {
        printInOrder(left(root));
        printEntry(root->key);
        printInOrder(right(root));
    }
}

/**
 *  prints given binary search tree node in postorder.
 *  @param a binary search tree node.
*/
void printPostOrder(Node root)
{
    if (root != NULL)
    {
        printPostOrder(left(root));
        printPostOrder(right(root));
        printEntry(root->key);
    }
}

/**
 *  inserts a new binary search tree node with given key and parent node.
 *  @param item binary search tree node entry.
 *  @param a binary search tree node.
 *  @return new binary search tree node.
*/
Node insertNode(Entry item, Node root)
{
    if (root == NULL)
        return createBst(item, NULL, NULL);
    if (isEntryLower(root->key, item))
        return createBst(root->key, insertNode(item, left(root)), right(root));
    if (isEntryGreater(root->key, item))
        return createBst(root->key, left(root), insertNode(item, right(root)));
    return NULL;
}