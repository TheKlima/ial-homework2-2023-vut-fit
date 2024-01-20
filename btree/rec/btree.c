// File: btree.c
// Subject: IAL
// Homework: #2
// Author: Andrii Klymenko, FIT VUT
// Login: xklyme00
// Date: 29.10.2023

/*
 * Binární vyhledávací strom — rekurzivní varianta
 *
 * S využitím datových typů ze souboru btree.h a připravených koster funkcí
 * implementujte binární vyhledávací strom pomocí rekurze.
 */

#include "../btree.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Inicializace stromu.
 *
 * Uživatel musí zajistit, že inicializace se nebude opakovaně volat nad
 * inicializovaným stromem. V opačném případě může dojít k úniku paměti (memory
 * leak). Protože neinicializovaný ukazatel má nedefinovanou hodnotu, není
 * možné toto detekovat ve funkci. 
 */
void bst_init(bst_node_t **tree) {
    if(tree != NULL)
    {
        *tree = NULL;
    }
}

/*
 * Vyhledání uzlu v stromu.
 *
 * V případě úspěchu vrátí funkce hodnotu true a do proměnné value zapíše
 * hodnotu daného uzlu. V opačném případě funkce vrátí hodnotu false a proměnná
 * value zůstává nezměněná.
 * 
 * Funkci implementujte rekurzivně bez použité vlastních pomocných funkcí.
 */
bool bst_search(bst_node_t *tree, char key, int *value) {
    if(tree != NULL && value != NULL)
    {
        if(tree->key == key) // if we have found a node that we need
        {
            *value = tree->value;
            return true;
        }

        if(key > tree->key)
        {
            return bst_search(tree->right, key, value); // go to right subtree
        }
        else
        {
            return bst_search(tree->left, key, value); // go to left subtree
        }
    }

    return false;
}

/*
 * Vložení uzlu do stromu.
 *
 * Pokud uzel se zadaným klíče už ve stromu existuje, nahraďte jeho hodnotu.
 * Jinak vložte nový listový uzel.
 *
 * Výsledný strom musí splňovat podmínku vyhledávacího stromu — levý podstrom
 * uzlu obsahuje jenom menší klíče, pravý větší. 
 *
 * Funkci implementujte rekurzivně bez použití vlastních pomocných funkcí.
 */
void bst_insert(bst_node_t **tree, char key, int value) {
    if(tree == NULL)
    {
        return;
    }

    if((*tree) == NULL) // if we have reached the place where we need to create a new node
    {
        *tree = (bst_node_t*) malloc(sizeof(bst_node_t)); // allocate memory for new node

        if((*tree) == NULL)
        {
            return;
        }

        // add data to new node
        (*tree)->key = key;
        (*tree)->value = value;
        (*tree)->left = NULL;
        (*tree)->right = NULL;
    }
    else if(key > (*tree)->key)
    {
        bst_insert(&((*tree)->right), key, value); // go to right subtree
    }
    else if(key < (*tree)->key)
    {
        bst_insert(&((*tree)->left), key, value); // go to left subtree
    }
    else // if a node with key 'key' already exists in the tree
    {
        (*tree)->value = value; // change value of the node
    }
}

/*
 * Pomocná funkce která nahradí uzel nejpravějším potomkem.
 * 
 * Klíč a hodnota uzlu target budou nahrazeny klíčem a hodnotou nejpravějšího
 * uzlu podstromu tree. Nejpravější potomek bude odstraněný. Funkce korektně
 * uvolní všechny alokované zdroje odstraněného uzlu.
 *
 * Funkce předpokládá, že hodnota tree není NULL.
 * 
 * Tato pomocná funkce bude využitá při implementaci funkce bst_delete.
 *
 * Funkci implementujte rekurzivně bez použití vlastních pomocných funkcí.
 */
void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree) {
    if((*tree)->right != NULL) // if we haven't reached rightmost node
    {
        bst_replace_by_rightmost(target, &((*tree)->right)); // go to right node
    }
    else
    {
        if(target != NULL)
        {
            // add data to 'target' node
            target->key = (*tree)->key;
            target->value = (*tree)->value;
        }
        else
        {
            return;
        }

        bst_node_t* to_delete = *tree;
        *tree = to_delete->left; // 'bridging' node that will be deleted

        to_delete->left = NULL;
        free(to_delete);
        to_delete = NULL;
    }
}

/*
 * Odstranění uzlu ze stromu.
 *
 * Pokud uzel se zadaným klíčem neexistuje, funkce nic nedělá.
 * Pokud má odstraněný uzel jeden podstrom, zdědí ho rodič odstraněného uzlu.
 * Pokud má odstraněný uzel oba podstromy, je nahrazený nejpravějším uzlem
 * levého podstromu. Nejpravější uzel nemusí být listem.
 * 
 * Funkce korektně uvolní všechny alokované zdroje odstraněného uzlu.
 * 
 * Funkci implementujte rekurzivně pomocí bst_replace_by_rightmost a bez
 * použití vlastních pomocných funkcí.
 */
void bst_delete(bst_node_t **tree, char key) {
    if(tree == NULL || (*tree) == NULL)
    {
        return;
    }

    if(key < (*tree)->key)
    {
        bst_delete(&((*tree)->left), key); // go to the left subtree
    }
    else
    {
        if(key > (*tree)->key)
        {
            bst_delete(&((*tree)->right), key); // go to the right subtree
        }
        else // if we have found a node that we need to delete
        {
            if((*tree)->right == NULL && (*tree)->left == NULL) // if node that we need to delete has no children
            {
                free(*tree);
                *tree = NULL;
                return;
            }
            else // if there is at least one child
            {
                if((*tree)->right != NULL && (*tree)->left != NULL) // if node has two children
                {
                    bst_replace_by_rightmost(*tree, &((*tree)->left));
                }
                else
                {
                    bst_node_t* to_delete = *tree;

                    if((*tree)->right == NULL) // if node has only one child on the left side
                    {
                        (*tree)->right = NULL;
                        *tree = (*tree)->left; // 'bridging' node that will be deleted
                    }
                    else // if node has only one child on the right side
                    {
                        (*tree)->left = NULL;
                        *tree = (*tree)->right; // 'bridging' node that will be deleted
                    }

                    free(to_delete);
                    to_delete = NULL;
                }
            }
        }
    }
}

/*
 * Zrušení celého stromu.
 * 
 * Po zrušení se celý strom bude nacházet ve stejném stavu jako po 
 * inicializaci. Funkce korektně uvolní všechny alokované zdroje rušených 
 * uzlů.
 * 
 * Funkci implementujte rekurzivně bez použití vlastních pomocných funkcí.
 */
void bst_dispose(bst_node_t **tree) {
    if(tree != NULL && (*tree) != NULL)
    {
        bst_dispose(&((*tree)->left));  // free left subtree
        bst_dispose(&((*tree)->right)); // free right subtree
        free(*tree);                    // free root node
        *tree = NULL;
    }
}

/*
 * Preorder průchod stromem.
 *
 * Pro aktuálně zpracovávaný uzel zavolejte funkci bst_add_node_to_items.
 *
 * Funkci implementujte rekurzivně bez použití vlastních pomocných funkcí.
 */
void bst_preorder(bst_node_t *tree, bst_items_t *items) {
    if(tree != NULL && items != NULL)
    {
        bst_add_node_to_items(tree, items); // firstly we process root node
        bst_preorder(tree->left, items);    // then left subtree
        bst_preorder(tree->right, items);   // then right subtree
    }
}

/*
 * Inorder průchod stromem.
 *
 * Pro aktuálně zpracovávaný uzel zavolejte funkci bst_add_node_to_items.
 *
 * Funkci implementujte rekurzivně bez použití vlastních pomocných funkcí.
 */
void bst_inorder(bst_node_t *tree, bst_items_t *items) {
    if(tree != NULL && items != NULL)
    {
        bst_inorder(tree->left, items);     // firstly we process left subtree
        bst_add_node_to_items(tree, items); // then root node
        bst_inorder(tree->right, items);    // then right subtree
    }
}

/*
 * Postorder průchod stromem.
 *
 * Pro aktuálně zpracovávaný uzel zavolejte funkci bst_add_node_to_items.
 *
 * Funkci implementujte rekurzivně bez použití vlastních pomocných funkcí.
 */
void bst_postorder(bst_node_t *tree, bst_items_t *items) {
    if(tree != NULL && items != NULL)
    {
        bst_postorder(tree->left, items);   // firstly we process left subtree
        bst_postorder(tree->right, items);  // then right subtree
        bst_add_node_to_items(tree, items); // then root node
    }
}
