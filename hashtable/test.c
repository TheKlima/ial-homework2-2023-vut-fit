#include "hashtable.h"
#include "test_util.h"
#include <stdio.h>
#include <stdlib.h>

#define INSERT_TEST_DATA(TABLE)                                                \
  ht_insert_many(TABLE, TEST_DATA, sizeof(TEST_DATA) / sizeof(TEST_DATA[0]));

const ht_item_t TEST_DATA[15] = {
    {"Bitcoin", 53247.71}, {"Ethereum", 3208.67}, {"Binance Coin", 409.15},
    {"Cardano", 1.82},     {"Tether", 0.86},      {"XRP", 0.93},
    {"Solana", 134.50},    {"Polkadot", 34.99},   {"Dogecoin", 0.22},
    {"USD Coin", 0.86},    {"Uniswap", 21.68},    {"Terra", 30.67},
    {"Litecoin", 156.87},  {"Avalanche", 47.03},  {"Chainlink", 21.90}};

void init_test() {
  printf("Hash Table - testing script\n");
  printf("---------------------------\n");
  HT_SIZE = 13;
  printf("\nSetting HT_SIZE to prime number (%i)\n", HT_SIZE);
  printf("\n");
}

TEST(test_table_init, "Initialize the table")
ht_init(test_table);
ENDTEST

TEST(test_search_nonexist, "Search for a non-existing item")
ht_init(test_table);
ht_search(test_table, "Ethereum");
ENDTEST

TEST(test_insert_simple, "Insert a new item")
ht_init(test_table);
ht_insert(test_table, "Ethereum", 3208.67);
ENDTEST

TEST(test_search_exist, "Search for an existing item")
ht_init(test_table);
ht_insert(test_table, "Ethereum", 3208.67);
ht_search(test_table, "Ethereum");
ENDTEST

TEST(test_insert_many, "Insert many new items")
ht_init(test_table);
INSERT_TEST_DATA(test_table)
ENDTEST

TEST(test_search_collision, "Search for an item with colliding hash")
ht_init(test_table);
INSERT_TEST_DATA(test_table)
ht_search(test_table, "Terra");
ENDTEST

TEST(test_insert_update, "Update an item")
ht_init(test_table);
INSERT_TEST_DATA(test_table)
ht_insert(test_table, "Ethereum", 12.34);
ENDTEST

TEST(test_get, "Get an item's value")
ht_init(test_table);
INSERT_TEST_DATA(test_table)
ht_get(test_table, "Ethereum");
ENDTEST

TEST(test_delete, "Delete an item")
ht_init(test_table);
INSERT_TEST_DATA(test_table)
ht_delete(test_table, "Terra");
ENDTEST

TEST(test_delete_all, "Delete all the items")
ht_init(test_table);
INSERT_TEST_DATA(test_table)
ht_delete_all(test_table);
ENDTEST

int main(int argc, char *argv[]) {
  init_uninitialized_item();
  init_test();

  test_table_init();
  test_search_nonexist();
  test_insert_simple();
  test_search_exist();
  test_insert_many();
  test_search_collision();
  test_insert_update();
  test_get();
  test_delete();
  test_delete_all();

  free(uninitialized_item);
}


// some tests from discord

//#include "hashtable.h"
//#include "test_util.h"
//#include <stdio.h>
//#include <stdlib.h>
//
//#define INSERT_TEST_DATA(TABLE)                                                \
//  ht_insert_many(TABLE, TEST_DATA, sizeof(TEST_DATA) / sizeof(TEST_DATA[0]));
//
//const ht_item_t TEST_DATA[15] = {
//        {"Bitcoin", 53247.71}, {"Ethereum", 3208.67}, {"Binance Coin", 409.15},
//        {"Cardano", 1.82},     {"Tether", 0.86},      {"XRP", 0.93},
//        {"Solana", 134.50},    {"Polkadot", 34.99},   {"Dogecoin", 0.22},
//        {"USD Coin", 0.86},    {"Uniswap", 21.68},    {"Terra", 30.67},
//        {"Litecoin", 156.87},  {"Avalanche", 47.03},  {"Chainlink", 21.90}};
//
//int tests_passed = 0;
//int tests_failed;
//
//void red() {
//    printf("\033[1;31m");
//}
//
//void green() {
//    printf("\033[1;32m");
//}
//
//void cyan() {
//    printf("\033[1;36m");
//}
//
//void reset_color(){
//    printf("\033[0m");
//}
//
//void init_test() {
//    printf("Hash Table - testing script\n");
//    printf("---------------------------\n");
//    HT_SIZE = 13;
//    printf("\nSetting HT_SIZE to prime number (%i)\n", HT_SIZE);
//    printf("\n");
//}
//
//TEST(test_table_init, "Initialize the table")
//    ht_init(test_table);
//    cyan();
//    printf("\n");
//    printf("----------------------------------------------------------------------------------------\n");
//    printf("|  If you implemented the ht_init() correctly, every output should look like this now  |\n");
//    printf("----------------------------------------------------------------------------------------\n");
//    printf("\n");
//    printf("------------HASH TABLE--------------                                                  \n");
//    printf("0:                                                                                    \n");
//    printf("1:                                                                                    \n");
//    printf("2:                                                                                    \n");
//    printf("3:                                                                                    \n");
//    printf("4:                                                                                    \n");
//    printf("5:                                                                                    \n");
//    printf("6:                                                                                    \n");
//    printf("7:                                                                                    \n");
//    printf("8:                                                                                    \n");
//    printf("9:                                                                                    \n");
//    printf("10:                                                                                   \n");
//    printf("11:                                                                                   \n");
//    printf("11:                                                                                   \n");
//    printf("------------------------------------                                                  \n");
//    printf("Total items in hash table: 0                                                          \n");
//    printf("Maximum hash collisions: 0                                                            \n");
//    printf("------------------------------------                                                  \n");
//    printf("\n");
//    reset_color();
//ENDTEST
//
//TEST(test_search_nonexist, "Search for a non-existing item")
//    ht_init(test_table);
//    ht_item_t *test_item;
//    test_item = ht_search(test_table, "Ethereum");
//
//    if (test_item == NULL) {
//        green();
//        printf("\nThe item Ethereum was not found! [TEST PASSED ✓]\n");
//        tests_passed++;
//    } else {
//        red();
//        printf("\nThe item Etherum was found! [TEST FAILED ☓]\n");
//    }
//
//    reset_color();
//ENDTEST
//
//TEST(test_insert_simple, "Insert a new item")
//    ht_init(test_table);
//    ht_insert(test_table, "Ethereum", 3208.67);
//    cyan();
//    printf("\n");
//    printf("------------------------------------------------------------------------------------------\n");
//    printf("|  If you implemented the ht_insert() correctly, output below should look like this now  |\n");
//    printf("------------------------------------------------------------------------------------------\n");
//    printf("\n");
//    printf("------------HASH TABLE--------------\n");
//    printf("0: (Ethereum,3208.67)\n");
//    printf("1:\n");
//    printf("2:\n");
//    printf("3:\n");
//    printf("4:\n");
//    printf("5:\n");
//    printf("6:\n");
//    printf("7:\n");
//    printf("8:\n");
//    printf("9:\n");
//    printf("10:\n");
//    printf("11:\n");
//    printf("11:\n");
//    printf("------------------------------------\n");
//    printf("Total items in hash table: 1\n");
//    printf("Maximum hash collisions: 0\n");
//    printf("------------------------------------\n");
//    reset_color();
//ENDTEST
//
//TEST(test_search_exist, "Search for an existing item")
//    ht_init(test_table);
//    ht_insert(test_table, "Ethereum", 3208.67);
//    ht_item_t *test_item;
//    test_item = ht_search(test_table, "Ethereum");
//    if (test_item == NULL) {
//        red();
//        printf("\nThe item was not found! [TEST FAILED ☓]\n");
//    } else {
//        green();
//        printf("\nThe item Etherum was found! [TEST PASSED ✓]\n");
//        printf("The item Etherum has a value of: %.2f\n", test_item->value);
//        tests_passed++;
//    }
//    reset_color();
//ENDTEST
//
//TEST(test_insert_many, "Insert many new items")
//    ht_init(test_table);
//    INSERT_TEST_DATA(test_table)
//    cyan();
//    printf("\n");
//    printf("------------------------------------------------------------------------------------------\n");
//    printf("|  If you implemented the ht_insert() correctly, output below should look like this now  |\n");
//    printf("------------------------------------------------------------------------------------------\n");
//    printf("\n");
//    printf("------------HASH TABLE--------------\n");
//    printf("0: (Ethereum,3208.67)\n");
//    printf("1:\n");
//    printf("2:\n");
//    printf("3: (Avalanche,47.03)(Uniswap,21.68)(Dogecoin,0.22)\n");
//    printf("4: (Chainlink,21.90)(Terra,30.67)(XRP,0.93)\n");
//    printf("5: (Litecoin,156.87)\n");
//    printf("6:\n");
//    printf("7:\n");
//    printf("8: (Cardano,1.82)\n");
//    printf("9: (Solana,134.50)(Binance Coin,409.15)\n");
//    printf("10: (Tether,0.86)\n");
//    printf("11: (Bitcoin,53247.71)\n");
//    printf("11: (USD Coin,0.86)(Polkadot,34.99)\n");
//    printf("------------------------------------\n");
//    printf("Total items in hash table: 15\n");
//    printf("Maximum hash collisions: 2\n");
//    printf("------------------------------------\n");
//    reset_color();
//ENDTEST
//
//TEST(test_search_collision, "Search for an item with colliding hash")
//    ht_init(test_table);
//    INSERT_TEST_DATA(test_table)
//    ht_item_t *test_item;
//    test_item = ht_search(test_table, "Terra");
//
//    if (test_item == NULL) {
//        red();
//        printf("\nThe item with colliding hash was not found! [TEST FAILED ☓]\n");
//    } else {
//        green();
//        printf("\nThe item with colliding hash Terra was found! [TEST PASSED ✓]\n");
//        printf("The item with colliding hash Terra has a value of: %.2f\n", test_item->value);
//        tests_passed++;
//    }
//    reset_color();
//ENDTEST
//
//TEST(test_insert_update, "Update an item")
//    ht_init(test_table);
//    INSERT_TEST_DATA(test_table)
//    ht_insert(test_table, "Ethereum", 12.34);
//    ht_item_t *test_item;
//    test_item = ht_search(test_table, "Ethereum");
//    if ((test_item->value - 12.34) < 0.00001){
//        green();
//        printf("\nValue of item Ethereum was updated correctly! [TEST PASSED ✓]\n");
//        printf("New value of item Ethereum is: 12.34\n");
//        tests_passed++;
//    } else {
//        red();
//        printf("\nValue of item Ethereum was NOT updated correctly! [TEST FAILED ☓]\n");
//    }
//    reset_color();
//ENDTEST
//
//TEST(test_get, "Get an item's value")
//    ht_init(test_table);
//    INSERT_TEST_DATA(test_table)
//    float *value;
//    value = ht_get(test_table, "Ethereum");
//    if (value == NULL){
//        red();
//        printf("\nThe item Ethereums' value was NOT found! [TEST FAILED ☓]\n");
//    } else{
//        green();
//        printf("\nThe item Ethereums' value was found! [TEST PASSED ✓]\n");
//        printf("The item Ethereum has a value of: %.2f\n", *value);
//        tests_passed++;
//    }
//    reset_color();
//ENDTEST
//
//TEST(test_delete, "Delete an item")
//    ht_init(test_table);
//    INSERT_TEST_DATA(test_table)
//    ht_delete(test_table, "Terra");
//    ht_item_t *test_item;
//    test_item = ht_search(test_table, "Terra");
//    if (test_item == NULL){
//        green();
//        printf("\nThe item Terra was deleted correctly! [TEST PASSED ✓]\n");
//        tests_passed++;
//    } else {
//        red();
//        printf("\nThe item Terra was NOT deleted correctly! [TEST FAILED ☓]\n");
//    }
//    reset_color();
//ENDTEST
//
//TEST(test_delete_all, "Delete all the items")
//    ht_init(test_table);
//    INSERT_TEST_DATA(test_table)
//    ht_delete_all(test_table);
//    cyan();
//    printf("\n");
//    printf("-------------------------------------------------------------------------------------------\n");
//    printf("|  If you implemented the delete_all() correctly, output below should look like this now  |\n");
//    printf("-------------------------------------------------------------------------------------------\n");
//    printf("\n");
//    printf("------------HASH TABLE--------------\n");
//    printf("0:\n");
//    printf("1:\n");
//    printf("2:\n");
//    printf("3:\n");
//    printf("4:\n");
//    printf("5:\n");
//    printf("6:\n");
//    printf("7:\n");
//    printf("8:\n");
//    printf("9:\n");
//    printf("10:\n");
//    printf("11:\n");
//    printf("11:\n");
//    printf("------------------------------------\n");
//    printf("Total items in hash table: 0\n");
//    printf("Maximum hash collisions: 0\n");
//    printf("------------------------------------\n");
//    reset_color();
//ENDTEST
//
//
//
//
//int main(int argc, char *argv[]) {
//    init_uninitialized_item();
//    init_test();
//
//    test_table_init();
//    test_search_nonexist();
//    test_insert_simple();
//    test_search_exist();
//    test_insert_many();
//    test_search_collision();
//    test_insert_update();
//    test_get();
//    test_delete();
//    test_delete_all();
//
//    free(uninitialized_item);
//
//    tests_failed = 6 - tests_passed;
//    printf("\n");
//    printf("---------- TESTS SUMMARY ----------\n");
//    printf("|                                 |\n");
//    printf("|");
//    green();
//    printf(" TESTS PASSED: %d", tests_passed);
//    reset_color();
//    printf("                 |\n");
//    printf("|");
//    red();
//    printf(" TESTS FAILED: %d", tests_failed);
//    reset_color();
//    printf("                 |\n");
//    printf("|                                 |\n");
//    printf("-----------------------------------\n");
//    printf("\n");
//    reset_color();
//}

// end of some tests from discord


// some another tests from discord

//#include <assert.h>
//#include <string.h>
//#define NR_TESTS 1000
//#define TEST_SIZE 101
//
//#include "hashtable.h"
//#include "test_util.h"
//#include <stdio.h>
//#include <stdlib.h>
//
//#define INSERT_TEST_DATA(TABLE)                                                \
//    ht_insert_many(TABLE, TEST_DATA, sizeof(TEST_DATA) / sizeof(TEST_DATA[0]));
//
//const ht_item_t TEST_DATA[15] = {
//        {"Bitcoin", 53247.71, NULL},    {"Ethereum", 3208.67, NULL},
//        {"Binance Coin", 409.15, NULL}, {"Cardano", 1.82, NULL},
//        {"Tether", 0.86, NULL},         {"XRP", 0.93, NULL},
//        {"Solana", 134.50, NULL},       {"Polkadot", 34.99, NULL},
//        {"Dogecoin", 0.22, NULL},       {"USD Coin", 0.86, NULL},
//        {"Uniswap", 21.68, NULL},       {"Terra", 30.67, NULL},
//        {"Litecoin", 156.87, NULL},     {"Avalanche", 47.03, NULL},
//        {"Chainlink", 21.90, NULL},
//};
//
//void init_test() {
//    printf("Hash Table - testing script\n");
//    printf("---------------------------\n");
//    HT_SIZE = 13;
//    printf("\nSetting HT_SIZE to prime number (%i)\n", HT_SIZE);
//    printf("\n");
//}
//
//TEST(test_table_init, "Initialize the table")
//    ht_init(test_table);
//ENDTEST
//
//TEST(test_search_nonexist, "Search for a non-existing item")
//    ht_init(test_table);
//    ht_search(test_table, "Ethereum");
//ENDTEST
//
//TEST(test_insert_simple, "Insert a new item")
//    ht_init(test_table);
//    ht_insert(test_table, "Ethereum", 3208.67);
//ENDTEST
//
//TEST(test_search_exist, "Search for an existing item")
//    ht_init(test_table);
//    ht_insert(test_table, "Ethereum", 3208.67);
//    ht_search(test_table, "Ethereum");
//ENDTEST
//
//TEST(test_insert_many, "Insert many new items")
//    ht_init(test_table);
//    INSERT_TEST_DATA(test_table)
//ENDTEST
//
//TEST(test_search_collision, "Search for an item with colliding hash")
//    ht_init(test_table);
//    INSERT_TEST_DATA(test_table)
//    ht_search(test_table, "Terra");
//ENDTEST
//
//TEST(test_insert_update, "Update an item")
//    ht_init(test_table);
//    INSERT_TEST_DATA(test_table)
//    ht_insert(test_table, "Ethereum", 12.34);
//ENDTEST
//
//TEST(test_get, "Get an item's value")
//    ht_init(test_table);
//    INSERT_TEST_DATA(test_table)
//    ht_get(test_table, "Ethereum");
//ENDTEST
//
//TEST(test_delete, "Delete an item")
//    ht_init(test_table);
//    INSERT_TEST_DATA(test_table)
//    ht_delete(test_table, "Terra");
//ENDTEST
//
//TEST(test_delete_all, "Delete all the items")
//    ht_init(test_table);
//    INSERT_TEST_DATA(test_table)
//    ht_delete_all(test_table);
//ENDTEST
//
//// ipt enjoyers can check in how many cases this will return zero
//float rand_nonzero() { return rand() + rand() + rand(); }
//
//char rand_ascii() { return (rand() % 127) + 1; }
//
//void check_values(ht_table_t *table, char keys[TEST_SIZE][6], float *results) {
//    for (int i = 0; i < TEST_SIZE; i++) {
//        ht_item_t *search = ht_search(table, keys[i]);
//        float *get = ht_get(table, keys[i]);
//
//        if (results[i] == 0.0) {
//            assert(search == NULL);
//            assert(get == NULL);
//        } else {
//            assert(!strcmp(search->key, keys[i]));
//            assert(search->value == results[i]);
//            assert(*get == results[i]);
//
//            // lets test the ptr is actually writable
//            float newval = rand_nonzero();
//            *get = newval;
//            results[i] = newval;
//        }
//    }
//}
//
//TEST(test_chonker, "Test everything, everywhere, all at once")
//
//    for (int test_nr = 0; test_nr < NR_TESTS; test_nr++) {
//        ht_table_t table;
//        ht_init(&table);
//        char keys[TEST_SIZE][6]; // 5 chars for input + 1 for null byte
//        float results[TEST_SIZE];
//
//        for (int i = 0; i < TEST_SIZE; i++) {
//            // when writing tests, you can do ugly shit like this
//            // and no one can tell you anything :feelsGoodMan:
//            keys[i][0] = rand_ascii();
//            keys[i][1] = rand_ascii();
//            keys[i][2] = rand_ascii();
//            keys[i][3] = rand_ascii();
//            keys[i][4] = rand_ascii();
//            keys[i][5] = '\0';
//
//            results[i] = rand_nonzero();
//            ht_insert(&table, keys[i], results[i]);
//        }
//
//        check_values(&table, keys, results);
//
//        // insert some existing values again
//        for (int i = 0; i < TEST_SIZE; i++) {
//            if (rand() % 2 == 0) {
//                float newval = rand_nonzero();
//                ht_insert(&table, keys[i], newval);
//                results[i] = newval;
//            }
//        }
//
//        check_values(&table, keys, results);
//
//        // delete some values
//        for (int i = 0; i < TEST_SIZE; i++) {
//            if (rand() % 2 == 0) {
//                ht_delete(&table, keys[i]);
//                results[i] = 0.0;
//            }
//        }
//
//        check_values(&table, keys, results);
//
//        // delete everything and check again
//        ht_delete_all(&table);
//        for (int i = 0; i < TEST_SIZE; i++)
//            results[i] = 0.0;
//
//        check_values(&table, keys, results);
//    }
//
//    ht_init(test_table);
//ENDTEST
//
//int main() {
//    srand(42);
//
//    init_uninitialized_item();
//    init_test();
//
//    test_table_init();
//    test_search_nonexist();
//    test_insert_simple();
//    test_search_exist();
//    test_insert_many();
//    test_search_collision();
//    test_insert_update();
//    test_get();
//    test_delete();
//    test_delete_all();
//    test_chonker();
//
//    free(uninitialized_item);
//    printf("If you don't see any assertion errors, the test passed\n");
//}

// end of some another tests from discord