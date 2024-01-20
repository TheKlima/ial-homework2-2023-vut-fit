// File: exa.c
// Subject: IAL
// Homework: #2
// Author: Andrii Klymenko, FIT VUT
// Login: xklyme00
// Date: 11.11.2023

/*
 * Použití binárních vyhledávacích stromů.
 *
 * S využitím Vámi implementovaného binárního vyhledávacího stromu (soubory ../iter/btree.c a ../rec/btree.c)
 * implementujte funkci letter_count. Výstupní strom může být značně degradovaný (až na úroveň lineárního seznamu) 
 * a tedy implementujte i druhou funkci (bst_balance), která strom, na požadavek uživatele, vybalancuje.
 * Funkce jsou na sobě nezávislé a tedy automaticky NEVOLEJTE bst_balance v letter_count.
 * 
 */

#include "../btree.h"
#include <stdio.h>
#include <stdlib.h>


/**
 * Vypočítání frekvence výskytů znaků ve vstupním řetězci.
 * 
 * Funkce inicilializuje strom a následně zjistí počet výskytů znaků a-z (case insensitive), znaku 
 * mezery ' ', a ostatních znaků (ve stromu reprezentováno znakem podtržítka '_'). Výstup je v 
 * uložen ve stromu.
 * 
 * Například pro vstupní řetězec: "abBccc_ 123 *" bude strom po běhu funkce obsahovat:
 * 
 * key | value
 * 'a'     1
 * 'b'     2
 * 'c'     3
 * ' '     2
 * '_'     5
 * 
 * Pro implementaci si můžete v tomto souboru nadefinovat vlastní pomocné funkce.
*/
void letter_count(bst_node_t **tree, char *input) {
    if(tree == NULL || input == NULL)
    {
        return;
    }

    bst_init(tree);

    int ascii[128] = {0, }; // array that counts number of appearances of each character in string 'input'

    for(int i = 0; input[i] != '\0'; i++) // loop through whole string 'input'
    {
        int c = (int) input[i]; // get character from the string

        if((c >= 'a' && c <= 'z') || c == ' ')
        {
            ascii[c]++;
        }
        else if(c >= 'A' && c <= 'Z')
        {
            ascii[c + ('a' - 'A')]++; // function is case-insensitive
        }
        else // other characters
        {
            ascii['_']++;
        }
    }

    for(int i = 0; i <= 'z'; i++) // loop through 'ascii' array
    {
        if(ascii[i] > 0) // if we have at least one appearance of certain character in string 'input'
        {
            bst_insert(tree, (char) i, ascii[i]);
        }
    }
}


/**
 * @brief Creates balanced binary tree from the sorted (by value) array of nodes
 *
 * 'items' is array of nodes that holds sorted (by value) array of nodes.
 * This function takes nodes from this array and inserts them to the tree '*tree'
 * in such way that tree '*tree' becomes balanced.
 *
 * @param tree pointer to pointer (address of pointer) to the root node of the tree
 * @param l left index of the array of nodes
 * @param r right index of the array of nodes
 * @param items array of nodes
 */
void treeFromArray(bst_node_t** tree, int l, int r, bst_items_t* items)
{
    if(l <= r) // have we processed all nodes ?
    {
        int m = (l + r) / 2;                              // calculating middle index
        *tree = (bst_node_t*) malloc(sizeof(bst_node_t)); // allocate memory for new node in tree

        if(*tree == NULL)
        {
            return;
        }

        // add data to current node
        (*tree)->value = items->nodes[m]->value;
        (*tree)->key = items->nodes[m]->key;

        treeFromArray(&((*tree)->left), l, m - 1, items);  // building left subtree
        treeFromArray(&((*tree)->right), m + 1, r, items); // building right subtree
    }
    else // we have processed all nodes
    {
        *tree = NULL;
    }
}

/**
 * @brief Initializes array of nodes before its first usage
 *
 * @param items array of nodes
 */
void bstItemsInit(bst_items_t* items)
{
    items->nodes = NULL;
    items->size = 0;
    items->capacity = 0;
}

/**
 * @brief Deallocates dynamic memory of array of nodes and resets its data
 *
 * @param items array of nodes
 */
void bstItemsDestroy(bst_items_t* items)
{
    if(items != NULL)
    {
        if(items->capacity > 0) // if we have allocated some memory for array of nodes
        {
            free(items->nodes);
        }

        items->capacity = 0;
        items->size = 0;
    }
}


/**
 * Vyvážení stromu.
 * 
 * Vyvážený binární vyhledávací strom je takový binární strom, kde hloubka podstromů libovolného uzlu se od sebe liší maximálně o jedna.
 * 
 * Předpokládejte, že strom je alespoň inicializován. K získání uzlů stromu využijte vhodnou verzi vámi naimplmentovaného průchodu stromem.
 * Následně můžete například vytvořit nový strom, kde pořadím vkládaných prvků zajistíte vyváženost.
 *  
 * Pro implementaci si můžete v tomto souboru nadefinovat vlastní pomocné funkce. Není nutné, aby funkce fungovala *in situ* (in-place).
*/
void bst_balance(bst_node_t **tree) {
    if(tree == NULL)
    {
        return;
    }

    bst_items_t* items = (bst_items_t*) malloc(sizeof(bst_items_t)); // array of nodes

    if(items == NULL)
    {
        return;
    }

    bstItemsInit(items);

    // after this function call array of nodes 'items' will hold sorted by value array of tree '*tree' nodes
    bst_inorder(*tree, items);

    bst_node_t* balanced_tree = NULL;

    // after this function call 'balanced_tree' will hold a pointer to the root node of the balanced tree '*tree'
    treeFromArray(&balanced_tree, 0, items->size - 1, items);

    // cleanup array of nodes
    bstItemsDestroy(items);
    free(items);
    items = NULL;

    bst_dispose(tree); // cleanup original tree

    *tree = balanced_tree;

    balanced_tree = NULL;
}