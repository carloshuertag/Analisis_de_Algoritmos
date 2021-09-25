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
 *  inserts a new binary search tree node with given key and parent node.
 *  @param item binary search tree node entry.
 *  @param root binary search tree node.
 *  @return new binary search tree node.
*/
Node insertNode(Entry item, Node root)
{
    Node current = root;
    Node parent = NULL;
    while(current != NULL)
    {
        parent = current;
        current = (isEntryGreater(item, current->key)) ?
                    current->left : current->right;
    }
    if(parent == NULL)
        parent = createNode(item, 1, NULL, NULL);
    else if (isEntryGreater(item, parent->key))
        parent->left = createNode(item,  1, NULL, NULL);
    else if (isEntryLower(item, parent->key))
        parent->right = createNode(item, 1, NULL, NULL);
    else
        ++(parent->count);
    return parent;
}

/**
 *  checks given item existance on bst.
 *  @param root binary search tree root node.
 *  @param item binary search tree node entry.
 *  @return true if exists, fase if not
*/
bool searchKey(Node root, Entry item) {
    while (root != NULL)
    {
        if(isEntryLower(item, root->key))
            root = root->right;
        else if (isEntryGreater(item, root->key))
            root = root->left;
        else
            return true;
    }
    return false;
}

/**
 *  deletes a binary search tree given its root
 *  @param root binary search tree root node.
*/
void deleteTree(Node root){
    if(root == NULL)
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