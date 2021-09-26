/** 
 *  binary search tree node struct.
*/
typedef struct Node
{
    Entry key;
    unsigned int count;
    struct Node *left, *right;
} * Node;

/**
 *  creates a new binary search tree node with given nodes and a given entry.
 *  @param item binary search tree node entry.
 *  @param count binary search tree node entry times.
 *  @param lft binary search tree left node.
 *  @param rght binary search tree right node.
 *  @return new binary search tree node.
*/
Node createNode(Entry item, unsigned int count, Node lft, Node rght)
{
    Node node = (Node)malloc(sizeof(struct Node));
    node->key = item;
    node->count = 1;
    node->left = lft;
    node->right = rght;
    return node;
}

/**
 *  checks given item existance on bst.
 *  @param root binary search tree root node.
 *  @param item binary search tree node entry.
 *  @return node which its key is the item.
*/
Node searchNode(Node root, Entry item)
{
    Node current = root;
    while (current != NULL)
    {
        if (isEntryLower(item, current->key))
            if (current->right == NULL)
                break;
            else
                current = current->right;
        else if (isEntryGreater(item, current->key))
            if (current->left == NULL)
                break;
            else
                current = current->left;
        else
            return current;
    }
    return current;
}

/**
 *  inserts a new binary search tree node with given key and parent node.
 *  @param item binary search tree node entry.
 *  @param root binary search tree node.
 *  @return binary search tree node root.
*/
Node insertNode(Entry item, Node root)
{
    Node node = searchNode(root, item);
    if (node == NULL)
        return createNode(item, 1, NULL, NULL);
    else if (isEntryGreater(item, node->key))
        node->left = createNode(item, 1, NULL, NULL);
    else if (isEntryLower(item, node->key))
        node->right = createNode(item, 1, NULL, NULL);
    else
        ++(node->count);
    return root;
}

/**
 *  checks given item existance on bst.
 *  @param root binary search tree root node.
 *  @param item binary search tree node entry.
 *  @return true if exists, fase if not
*/
bool searchKey(Node root, Entry item)
{
    return item == searchNode(root, item)->key;
}

/**
 *  deletes a binary search tree given its root
 *  @param root binary search tree root node.
*/
void deleteTree(Node root)
{
    if (root == NULL)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

/**
 *  prints given binary search tree node in inorder.
 *  @param root binary search tree root node.
*/
void printInOrder(Node root)
{
    if (root != NULL)
    {
        printInOrder(root->left);
        printEntry(root->key);
        printInOrder(root->right);
    }
}
