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
 *  @param lft binary search tree left node.
 *  @param rght binary search tree right node.
 *  @return new binary search tree node.
*/
Node createNode(Entry item, Node lft, Node rght)
{
    Node node = (Node)malloc(sizeof(struct Node));
    node->key = item;
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
    Node newNode = createNode(item, NULL, NULL);
    Node current = root;
    Node aux = NULL;
    while(current != NULL)
    {
        aux = current;
        current = (isEntryGreater(item, current->key)) ?
                    current->left: current->right;
    }
    if(aux == NULL)
        aux = newNode;
    else if (isEntryGreater(item, aux->key))
        aux->left = newNode;
    else
        aux->right = newNode;
    return aux;
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