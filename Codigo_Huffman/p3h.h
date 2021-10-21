#define bitMask(bpos) 1 << bpos
#define getBitAt(var, bpos) (*(unsigned *)&var & bitMask(bpos)) ? 1 : 0
#define turnBitOnAt(var, bpos) *(unsigned *)&var |= bitMask(bpos)
#define turnBitOffAt(var, bpos) *(unsigned *)&var &= ~(bitMask(bpos))
#define flipBitAt(var, bpos) *(unsigned *)&var ^= bitMask(bpos)
#define NOITEM 257
#define NOCOUNT 0

/** 
 *   binary tree node struct.
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
 *  creates the binary tree to Huffman code a file, with a given frequency table.
 *  @param arr nx2 dimensions array in which elements are definied.
 *  like this: arr[x][0] for the element and its frequenct arr[x][1]
 *  @param n dimension of the array of the 2 dimensions array.
 *  @return binary tree root in which is built the tree to Hufman code.
*/
Node createTree(unsigned int arr[][2], int n)
{
    Node nodeArr[2 * n]; //max si<e since it will renove 2 or 1 nodes and add 1
    int i;
    for (i = 0; i < n; i++)
    { // initilializing nodes
        nodeArr[i] = createNode(arr[i][0], arr[i][1], NULL, NULL);
    }
    int end = n, lowest1, lowest2, index1, index2;
    int j;
    for (j = 0; j < n - 1; j++)
    {
        lowest1 = lowest2 = index1 = index2 = INT_MAX;
        for (i = 0; i < end; i++)
        { // find the lowest two nodes
            if (nodeArr[i]->count < lowest1)
            {
                lowest2 = lowest1;
                index2 = index1;
                lowest1 = nodeArr[i]->count;
                index1 = i;
            }
            else if (nodeArr[i]->count < lowest2)
            {
                lowest2 = nodeArr[i]->count;
                index2 = i;
            }
        }
        // build a new node in which the lowest two nodes will be merged
        nodeArr[end] = createNode(NOITEM, NOCOUNT, nodeArr[index1], nodeArr[index2]);
        end++; // up until 2n in its worst case
        //merged nodes will not be considered to find thw lowest pair again
        nodeArr[index1]->count = nodeArr[index2]->count = INT_MAX;
    }
    return nodeArr[end - 1]; // root in which is built the tree after merging
}

/**
 *  
*/
unsigned char *byteToWrite (int data, int *offset)
{
    unsigned char *byte = malloc();
    int b;
    for(b = 128; b >= 0; b = b >> 1)
    {
        if(data & b)
        {
            if(offset < 0)
            {

            }
            turnBitOnAt(byte, *offset);
        }
        else
            turnBitOffAt(byte, *offset);
        (*offset)--;
    }
    return byte;
}

/** 
 *  removes the extension from a given file path.
 *  @param filePath is the file path to process.
 *  @param extSep is the extension separator.
 *  @param pathSep is the path separator (use 0 to ignore).
 *  @return an allocated string identical to the original but
 *  with the extension removed. (NULL if filePath is null
 *  or the new string can't be allocated)
*/
char *remove_ext (char* filePath, char extSep, char pathSep) {
    char *retStr, *lastExt, *lastPath;
    // Error checks and allocate string.
    if (filePath == NULL) return NULL;
    if ((retStr = malloc (strlen (filePath) + 1)) == NULL)
    {
        perror("Error: string memory allocation failed");
        exit(1);
    }
    // Make a copy and find the relevant characters.
    strcpy (retStr, filePath);
    lastExt = strrchr (retStr, extSep);
    lastPath = (pathSep == 0) ? NULL : strrchr (retStr, pathSep);
    // If it has an extension separator.
    if (lastExt != NULL) { // and it's to the right of the path separator.
        if (lastPath != NULL)
        {
            if (lastPath < lastExt) 
            { // then remove it.
                *lastExt = '\0';
            }
        } else
        { // Has extension separator with no path separator.
            *lastExt = '\0';
        }
    }
    return retStr;
}
