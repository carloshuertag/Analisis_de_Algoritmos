/**
 *  binary search tree test program.
 *  @author @huerta2502
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "bst_entry.h"
#include "bst.h"

int main()
{
    Node niu = emptyBst();
    niu = insertNode(3, niu);
    niu = insertNode(2, niu);
    niu = insertNode(1, niu);
    niu = insertNode(5, niu);
    printInOrder(niu);
    return 0;
}