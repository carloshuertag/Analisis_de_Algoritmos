/**
 *  stores inorder traversal of given binary search tree
 *  into given array with given iterator.
 *  @param root binary search tree root node;
 *  @param arr array to store sorted elements
 *  @param i iterator
*/
void storeSorted(Node root, Entry *arr, int *i)
{
    if (!isEmptyBst(root)) 
    {
        storeSorted(root->left, arr, i);
        arr[(*i)++] = root->key;
        storeSorted(root->right, arr, i);
    }
}

/**
 *  sort given array of given size using a
 *  binary search tree.
 *  @param arr array to sort
 *  @param n array length
*/
void treeSort(int *arr, int n)
{
    Node root = insertNode(arr[0], emptyBst());
    int i = 0;
    for (i = 1; i < n; i++)
        root = insertNode(arr[i], root);
    i = 0;
    storeSorted(root, arr, &i);
}