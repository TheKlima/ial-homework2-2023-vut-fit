// File: hashtable.c
// Subject: IAL
// Homework: #2
// Author: Andrii Klymenko, FIT VUT
// Login: xklyme00
// Date: 8.11.2023

/*
 * Tabulka s rozptýlenými položkami
 *
 * S využitím datových typů ze souboru hashtable.h a připravených koster
 * funkcí implementujte tabulku s rozptýlenými položkami s explicitně
 * zretězenými synonymy.
 *
 * Při implementaci uvažujte velikost tabulky HT_SIZE.
 */

#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

int HT_SIZE = MAX_HT_SIZE;

/*
 * Rozptylovací funkce která přidělí zadanému klíči index z intervalu
 * <0,HT_SIZE-1>. Ideální rozptylovací funkce by měla rozprostírat klíče
 * rovnoměrně po všech indexech. Zamyslete sa nad kvalitou zvolené funkce.
 */
int get_hash(char *key) {
  int result = 1;
  int length = strlen(key);
  for (int i = 0; i < length; i++) {
    result += key[i];
  }
  return (result % HT_SIZE);
}

/*
 * Inicializace tabulky — zavolá sa před prvním použitím tabulky.
 */
void ht_init(ht_table_t *table) {
    if(table == NULL)
    {
        return;
    }

    for(int i = 0; i < MAX_HT_SIZE; i++)
    {
        (*table)[i] = NULL; // set every pointer to structure 'ht_item' to NULL
    }
}

/*
 * Vyhledání prvku v tabulce.
 *
 * V případě úspěchu vrací ukazatel na nalezený prvek; v opačném případě vrací
 * hodnotu NULL.
 */
ht_item_t *ht_search(ht_table_t *table, char *key) {
    if(table == NULL || key == NULL)
    {
        return NULL;
    }

    int hash = get_hash(key);

    ht_item_t* current = (*table)[hash];

    while(current != NULL) // while we haven't checked all elements with hash 'hash'
    {
        if(strcmp(key, current->key) == 0)
        {
            return current;
        }

        current = current->next; // move to the next element
    }

    return NULL;
}

/*
 * Vložení nového prvku do tabulky.
 *
 * Pokud prvek s daným klíčem už v tabulce existuje, nahraďte jeho hodnotu.
 *
 * Při implementaci využijte funkci ht_search. Pri vkládání prvku do seznamu
 * synonym zvolte nejefektivnější možnost a vložte prvek na začátek seznamu.
 */
void ht_insert(ht_table_t *table, char *key, float value) {
    if(table == NULL || key == NULL)
    {
        return;
    }

    ht_item_t* current = ht_search(table, key);

    if(current != NULL) // check if element with key 'key' already exists in the hash table
    {
        current->value = value;
    }
    else
    {
        current = (ht_item_t*) malloc(sizeof(ht_item_t)); // allocate memory for new item in hash table

        if(current == NULL)
        {
            return;
        }

        int hash = get_hash(key);

        current->next = (*table)[hash]; // make new element point to the first element with hash 'hash'
        current->key = key;
        current->value = value;

        (*table)[hash] = current;       // make new element first element of the single linked list with hash 'hash'
    }
}

/*
 * Získání hodnoty z tabulky.
 *
 * V případě úspěchu vrací funkce ukazatel na hodnotu prvku, v opačném
 * případě hodnotu NULL.
 *
 * Při implementaci využijte funkci ht_search.
 */
float *ht_get(ht_table_t *table, char *key) {
    if(table == NULL || key == NULL)
    {
        return NULL;
    }

    ht_item_t* current = ht_search(table, key);

    if(current != NULL) // if item with key 'key' already exists in the hash table
    {
        return &(current->value);
    }

    return NULL;
}

/*
 * Smazání prvku z tabulky.
 *
 * Funkce korektně uvolní všechny alokované zdroje přiřazené k danému prvku.
 * Pokud prvek neexistuje, funkce nedělá nic.
 *
 * Při implementaci NEPOUŽÍVEJTE funkci ht_search.
 */
void ht_delete(ht_table_t *table, char *key) {
    if(table == NULL || key == NULL)
    {
        return;
    }

    int hash = get_hash(key);

    ht_item_t* current = (*table)[hash];

    ht_item_t* prev = NULL; // pointer to the previous item of the current item

    while(current != NULL)  // while we haven't checked all elements with hash 'hash'
    {
        if(strcmp(key, current->key) == 0) // if we have found an element that we need to delete
        {
            // if the element that we want to delete is not the first element of the single linked list
            if(prev != NULL)
            {
                prev->next = current->next; // 'bridging' element that we will delete
            }
            else // if we need to delete the first element of the single linked list
            {
                (*table)[hash] = current->next; // 'bridging' element that we will delete
            }

            current->key = NULL;
            current->next = NULL;
            free(current);

            return;
        }

        // move to the next element
        prev = current;
        current = current->next;
    }
}

/*
 * Smazání všech prvků z tabulky.
 *
 * Funkce korektně uvolní všechny alokované zdroje a uvede tabulku do stavu po
 * inicializaci.
 */
void ht_delete_all(ht_table_t *table) {
    if(table == NULL)
    {
        return;
    }

    ht_item_t* current = NULL;
    ht_item_t* next = NULL;

    for(int i = 0; i < MAX_HT_SIZE; i++)
    {
        current = (*table)[i]; // pointer to the first element with hash 'i'

        while(current != NULL) // while we haven't processed all elements with hash 'i'
        {
            next = current->next; // update pointer to the next element

            current->key = NULL;
            current->next = NULL;
            free(current);

            current = next; // move to the next element
        }

        (*table)[i] = NULL; // set pointer to the first element with hash 'i' to NULL
    }
}
