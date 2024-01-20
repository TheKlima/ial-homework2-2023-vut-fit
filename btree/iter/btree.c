// File: btree.c
// Subject: IAL
// Homework: #2
// Author: Andrii Klymenko, FIT VUT
// Login: xklyme00
// Date: 29.10.2023

/*
 * Binární vyhledávací strom — iterativní varianta
 *
 * S využitím datových typů ze souboru btree.h, zásobníku ze souboru stack.h 
 * a připravených koster funkcí implementujte binární vyhledávací 
 * strom bez použití rekurze.
 */

#include "../btree.h"
#include "stack.h"
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
 * Funkci implementujte iterativně bez použité vlastních pomocných funkcí.
 */
bool bst_search(bst_node_t *tree, char key, int *value) {
    while(tree != NULL)
    {
        if(tree->key == key) // if the desired node is found
        {
            *value = tree->value;
            return true;
        }
        else if(key > tree->key)
        {
            tree = tree->right; // go to right subtree
        }
        else
        {
            tree = tree->left; // go to left subtree
        }
    }

    return false; // if we haven't found desired node
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
 * Funkci implementujte iterativně bez použití vlastních pomocných funkcí.
 */
void bst_insert(bst_node_t **tree, char key, int value) {
    if(tree == NULL)
    {
        return;
    }

    bst_node_t* current = *tree;
    bst_node_t* position = NULL; // tree node that has a pointer to node that we need to delete

    if(current != NULL)
    {
        do
        {
            position = current; // update position ptr

            if(key < current->key)
            {
                current = current->left; // go to left subtree
            }
            else if(key > current->key)
            {
                current = current->right; // go to right subtree
            }
            else // if node with key 'key' already exists in the tree
            {
                current->value = value; // update value of the node
                return;
            }
        } while(current != NULL); // loop until we haven't reached a place where we need to insert a new node
    }

    bst_node_t* new_node = (bst_node_t*) malloc(sizeof(bst_node_t));

    if(new_node == NULL)
    {
        return;
    }

    new_node->key = key;
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    if(position != NULL) // if tree was not empty
    {
        if(key < position->key)
        {
            position->left = new_node;
        }
        else
        {
            position->right = new_node;
        }
    }
    else // if tree was empty, new node becomes tree root node
    {
        *tree = new_node;
    }
}

/*
 * Pomocná funkce která nahradí uzel nejpravějším potomkem.
 * 
 * Klíč a hodnota uzlu target budou nahrazené klíčem a hodnotou nejpravějšího
 * uzlu podstromu tree. Nejpravější potomek bude odstraněný. Funkce korektně
 * uvolní všechny alokované zdroje odstraněného uzlu.
 *
 * Funkce předpokládá, že hodnota tree není NULL.
 * 
 * Tato pomocná funkce bude využita při implementaci funkce bst_delete.
 *
 * Funkci implementujte iterativně bez použití vlastních pomocných funkcí.
 */
void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree) {
    if(target == NULL)
    {
        return;
    }

    bst_node_t* current = *tree;
    bst_node_t* prev = NULL;

    while(current->right != NULL) // loop until we have reached the rightmost node
    {
        // updating prev and current pointers
        prev = current;
        current = current->right;
    }

    // copy data from current ptr to target ptr
    target->key = current->key;
    target->value = current->value;

    if(prev != NULL) // if *tree pointer is not pointing to the rightmost node
    {
        prev->right = current->left; // 'bridging' node that will be deleted
    }
    else // if *tree pointer is pointing to the rightmost node
    {
        (*tree) = (*tree)->left; // 'bridging' node that will be deleted
    }

    current->left = NULL;
    free(current);
    current = NULL;
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
 * Funkci implementujte iterativně pomocí bst_replace_by_rightmost a bez
 * použití vlastních pomocných funkcí.
 */
void bst_delete(bst_node_t **tree, char key) {
    if(tree == NULL || (*tree) == NULL)
    {
        return;
    }

    bst_node_t* current = *tree;
    bst_node_t* prev = NULL;

    bool isLeft = false; // is 'current' node left or right child of 'prev' node ?

    while(true)
    {
        if(current == NULL) // if node that we needed to delete doesn't exist in tree
        {
            return;
        }
        else if(key < current->key)
        {
            // updating prev and current pointers and 'isLeft'
            prev = current;
            current = current->left;
            isLeft = true; // 'current' node is left child of 'prev' node => isLeft = true
        }
        else if(key > current->key)
        {
            // updating prev and current pointers and 'isLeft'
            prev = current;
            current = current->right;
            isLeft = false; // 'current' node is right child of 'prev' node => isLeft = false
        }
        else // if we have found a node that we need to delete
        {
            break;
        }
    }

    if(current->right != NULL && current->left != NULL) // if node has two children
    {
        bst_replace_by_rightmost(current, &(current->left));
    }
    else // if node has 0 or 1 child
    {
        if(prev == NULL) // if we need to delete root node
        {
            if((*tree)->right == NULL) // if root node doesn't have right child
            {
                *tree = (*tree)->left; // left child becomes root node
            }
            else // if root node has left child or if it has no child at all
            {
                *tree = (*tree)->right; // right child becomes root node
            }
        }
        else if(current->right == NULL) // if node has one child on the left side
        {
            if(isLeft) // if 'current' node is left child of the 'prev' node
            {
                prev->left = current->left; // 'bridging' 'current' node
            }
            else // if 'current' node is right child of the 'prev' node
            {
                prev->right = current->left;  // 'bridging' 'current' node
            }

            current->left = NULL;
        }
        else if(current->left == NULL) // if node has only one child on the left side
        {
            if(isLeft) // if 'current' node is left child of the 'prev' node
            {
                prev->left = current->right; // 'bridging' 'current' node
            }
            else // if 'current' node is right child of the 'prev' node
            {
                prev->right = current->right; // 'bridging' 'current' node
            }

            current->right = NULL;
        }

        free(current);
        current = NULL;
    }
}

/*
 * Zrušení celého stromu.
 * 
 * Po zrušení se celý strom bude nacházet ve stejném stavu jako po 
 * inicializaci. Funkce korektně uvolní všechny alokované zdroje rušených 
 * uzlů.
 * 
 * Funkci implementujte iterativně s pomocí zásobníku a bez použití 
 * vlastních pomocných funkcí.
 */
void bst_dispose(bst_node_t **tree) {

    if(tree == NULL || *tree == NULL)
    {
        return;
    }

    stack_bst_t *stack = (stack_bst_t*) malloc(sizeof(stack_bst_t)); // stack of pointers

    if(stack == NULL)
    {
        return;
    }

    stack_bst_init(stack);

    bst_node_t *current = *tree;

    do
    {
        if(current == NULL)
        {
            if(!stack_bst_empty(stack))
            {
                current = stack_bst_top(stack); // take a node from the top of the stack

                if(current == NULL || stack_bst_pop(stack) == NULL)
                {
                    return;
                }
            }
        }
        else
        {
            if(current->right != NULL)
            {
                stack_bst_push(stack, current->right); // push right node to the stack
            }

            bst_node_t *tmp = current;
            current = current->left; // go to left subtree
            tmp->right = NULL;
            tmp->left = NULL;
            free(tmp);
            tmp = NULL;
        }
    } while(current != NULL || !stack_bst_empty(stack));

    free(stack);
    *tree = NULL;
}

/*
 * Pomocná funkce pro iterativní preorder.
 *
 * Prochází po levé větvi k nejlevějšímu uzlu podstromu.
 * Nad zpracovanými uzly zavolá bst_add_node_to_items a uloží je do zásobníku uzlů.
 *
 * Funkci implementujte iterativně s pomocí zásobníku a bez použití 
 * vlastních pomocných funkcí.
 */
void bst_leftmost_preorder(bst_node_t *tree, stack_bst_t *to_visit, bst_items_t *items) {
    while(tree != NULL)
    {
        stack_bst_push(to_visit, tree);     // push root node to the stack
        bst_add_node_to_items(tree, items); // process root node
        tree = tree->left;                  // then we need to process left subtree
    }
}

/*
 * Preorder průchod stromem.
 *
 * Pro aktuálně zpracovávaný uzel zavolejte funkci bst_add_node_to_items.
 *
 * Funkci implementujte iterativně pomocí funkce bst_leftmost_preorder a
 * zásobníku uzlů a bez použití vlastních pomocných funkcí.
 */
void bst_preorder(bst_node_t *tree, bst_items_t *items) {

    stack_bst_t *stack = (stack_bst_t*) malloc(sizeof(stack_bst_t));

    if(stack == NULL)
    {
        return;
    }

    stack_bst_init(stack);

    bst_leftmost_preorder(tree, stack, items);

    while(!stack_bst_empty(stack))
    {
        tree = stack_bst_top(stack); // pop unprocessed node from stack

        if(tree == NULL || stack_bst_pop(stack) == NULL)
        {
            return;
        }

        bst_leftmost_preorder(tree->right, stack, items);
    }

    free(stack);
}

/*
 * Pomocná funkce pro iterativní inorder.
 * 
 * Prochází po levé větvi k nejlevějšímu uzlu podstromu a ukládá uzly do
 * zásobníku uzlů.
 *
 * Funkci implementujte iterativně s pomocí zásobníku a bez použití 
 * vlastních pomocných funkcí.
 */
void bst_leftmost_inorder(bst_node_t *tree, stack_bst_t *to_visit) {
    while(tree != NULL)
    {
        stack_bst_push(to_visit, tree); // push root node
        tree = tree->left;              // go to left subtree
    }
}

/*
 * Inorder průchod stromem.
 *
 * Pro aktuálně zpracovávaný uzel zavolejte funkci bst_add_node_to_items.
 *
 * Funkci implementujte iterativně pomocí funkce bst_leftmost_inorder a
 * zásobníku uzlů a bez použití vlastních pomocných funkcí.
 */
void bst_inorder(bst_node_t *tree, bst_items_t *items) {
    stack_bst_t *stack = (stack_bst_t*) malloc(sizeof(stack_bst_t));

    if(stack == NULL)
    {
        return;
    }

    stack_bst_init(stack);

    bst_leftmost_inorder(tree, stack);

    while(!stack_bst_empty(stack))
    {
        tree = stack_bst_top(stack); // pop unprocessed node from the stack

        if(tree == NULL || stack_bst_pop(stack) == NULL)
        {
            return;
        }

        bst_add_node_to_items(tree, items);

        bst_leftmost_inorder(tree->right, stack);
    }

    free(stack);
}

/*
 * Pomocná funkce pro iterativní postorder.
 *
 * Prochází po levé větvi k nejlevějšímu uzlu podstromu a ukládá uzly do
 * zásobníku uzlů. Do zásobníku bool hodnot ukládá informaci, že uzel
 * byl navštíven poprvé.
 *
 * Funkci implementujte iterativně pomocí zásobníku uzlů a bool hodnot a bez použití
 * vlastních pomocných funkcí.
 */
void bst_leftmost_postorder(bst_node_t *tree, stack_bst_t *to_visit,
                            stack_bool_t *first_visit) {
    while(tree != NULL)
    {
        stack_bst_push(to_visit, tree);

        // push true to the stack of the booleans => identifying that we have already visited this node
        stack_bool_push(first_visit, true);

        tree = tree->left; // go to left subtree
    }
}

/*
 * Postorder průchod stromem.
 *
 * Pro aktuálně zpracovávaný uzel zavolejte funkci bst_add_node_to_items.
 *
 * Funkci implementujte iterativně pomocí funkce bst_leftmost_postorder a
 * zásobníku uzlů a bool hodnot a bez použití vlastních pomocných funkcí.
 */
void bst_postorder(bst_node_t *tree, bst_items_t *items) {
    stack_bst_t *ptr_stack = (stack_bst_t*) malloc(sizeof(stack_bst_t)); // stack of pointers to tree nodes

    if(ptr_stack == NULL)
    {
        return;
    }

    stack_bst_init(ptr_stack);

    // stack of booleans
    // it will tell us if we are going to the root node from the left subtree or from the right subtree
    stack_bool_t *bool_stack = (stack_bool_t*) malloc(sizeof(stack_bool_t));

    if(bool_stack == NULL)
    {
        return;
    }

    stack_bool_init(bool_stack);

    bst_leftmost_postorder(tree, ptr_stack, bool_stack);

    bool isFromLeft = false; // are we going from the left subtree or from the right subtree to the root node ?

    while(!stack_bst_empty(ptr_stack))
    {
        tree = stack_bst_top(ptr_stack);

        if(tree == NULL)
        {
            return;
        }

        isFromLeft = stack_bool_top(bool_stack);
        stack_bool_pop(bool_stack);

        if(isFromLeft) // coming from left subtree => we will go to right
        {
            stack_bool_push(bool_stack, false);
            bst_leftmost_postorder(tree->right, ptr_stack, bool_stack);
        }
        else // coming from right subtree => pop node from the stack and process this node
        {
            tree = stack_bst_pop(ptr_stack);

            if(tree == NULL)
            {
                return;
            }

            bst_add_node_to_items(tree, items);
        }
    }

    free(ptr_stack);
    free(bool_stack);
}
