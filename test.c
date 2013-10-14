/* This file contains what could be called a set of unit tests for the 
 * accompanying skip list implementation. These functions provide examples
 * of how to use the list calls and manage the pointers they return.
 *
 * (C) 2013 by Troy Deck; see LICENSE.txt for details
 */
#include "test.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Simply runs all the test functions
int main() {
    int err;
    if ((err = test_get_set())) return err;
    if ((err = test_unset())) return err;
    if ((err = test_hundred_inserts())) return err;

    return E_OK;
}


// Tests that skip-list initialization, get, and set methods appear
// to be working correctly for a list with three elements.
int test_get_set() {
    int err;

    printf("Starting test_get_set:\n");

    // Try to allocate a list
    printf("\tAllocating a list...\n");
    sl_entry * head = sl_init();
    if (!head) {
        printf("\tFAIL: Initialization returned null pointer.\n");
        return E_NULL_INIT;
    }

    // Insert three elements
    printf("\tInserting three elements...\n");
    sl_set(head, "Bravo", "B");
    sl_set(head, "A", "Alpha");
    sl_set(head, "Charlie", "C");

    // Extract elements and compare with our expectations
    // "A" -> "Alpha"
    printf("\tLooking up first element...\n");
    if ((err = assert_sl_get(head, "A", "Alpha"))) return err;

    // "Bravo" -> "B"
    printf("\tLooking up second element...\n");
    if ((err = assert_sl_get(head, "Bravo", "B"))) return err;

    // "Charlie" -> "C"
    printf("\tLooking up third element...\n");
    if ((err = assert_sl_get(head, "Charlie", "C"))) return err;

    // Now test extracting something not in the list
    printf("\tLooking up nonexistent element...\n");
    if ((err = assert_sl_get(head, "Delta", NULL))) return err;

    // Deallocate the list
    printf("\tFreeing the list...\n");
    sl_destroy(head);
    head = NULL;
    
    printf("\tPASS: test_get_set passed\n");
    return E_OK;
}

// Tests that unset elements are correctly removed from the skip list,
// while preserving the list's structure.
int test_unset() {
    int err;
    printf("Starting test_unset:\n");

    // Try to allocate a list
    printf("\tAllocating a list...\n");
    sl_entry * head = sl_init();
    if (!head) {
        printf("\tFAIL: Initialization returned null pointer.\n");
        return E_NULL_INIT;
    }

    // Put three elements in the list
    printf("\tInserting three elements...\n");
    sl_set(head, "333", "Three");
    sl_set(head, "222", "Two");
    sl_set(head, "111", "One");

    // Unset a nonexistent element
    printf("\tUnsetting a nonexistent element...\n");
    sl_unset(head, "999"); 
    
    // Check all three values
    printf("\tChecking list values...\n");
    if ((err = assert_sl_get(head, "111", "One"))) return err;
    if ((err = assert_sl_get(head, "222", "Two"))) return err;
    if ((err = assert_sl_get(head, "333", "Three"))) return err;

    // Unset the second list element
    printf("\tUnsetting the second element...\n");
    sl_unset(head, "222");

    // Check all three values again
    printf("\tChecking list values...\n");
    if ((err = assert_sl_get(head, "111", "One"))) return err;
    if ((err = assert_sl_get(head, "222", NULL))) return err;
    if ((err = assert_sl_get(head, "333", "Three"))) return err;
    
    // Deallocate the list
    sl_destroy(head);
    head = NULL;

    printf("\tPASS: test_unset passed\n");
    return E_OK;
}

// A bulk test of set, unset, and get
int test_hundred_inserts() {
    int err;
    printf("Starting test_hundred_inserts:\n");
    
    // Try to allocate a list
    printf("\tAllocating a list...\n");
    sl_entry * head = sl_init();
    if (!head) {
        printf("\tFAIL: Initialization returned null pointer.\n");
        return E_NULL_INIT;
    }

    // Insert 100 elements but unset every odd element
    // after insertion
    printf("\tPerforming 100 sets and 50 unsets...\n");
    char num_buffer[3];
    int i;
    for (i = 99; i >= 0; -- i) {
        sprintf(num_buffer, "%d", i);
        sl_set(head, num_buffer, num_buffer);

        if (i % 2) {
            sl_unset(head, num_buffer);
        }
    }
    
    // Test each element 
    printf("\tVerifying list...\n");
    for (i = 0; i < 100; ++ i) {
        sprintf(num_buffer, "%d", i);

        if (i % 2) {
            // Expect a NULL result
            if ((err = assert_sl_get(head, num_buffer, NULL))) return err;
        } else {
            // Expect the correct numeric result
            if ((err = assert_sl_get(head, num_buffer, num_buffer))) return err;
        }
    }

    // Deallocate the list
    sl_destroy(head);

    head = NULL;
    printf("\tPASS: test_hundred_inserts passed\n");
    return E_OK;
}

// A utility function used to check that the expected value was
// returned from an sl_get call, since we do this a lot in these tests.
// Handles printing error messages, returning result codes, and special cases
// of returned and/or expected NULLs.
int assert_sl_get(sl_entry * head, char * key, char * expected_str) {
    char * result_str;
    result_str = sl_get(head, key);

    if (result_str) { // We got a non-NULL result
        if (expected_str) { // ... and we expected one
            if (strcmp(result_str, expected_str)) {
                printf(
                    "\tFAIL: Expected '%s' but got '%s'.\n", 
                    expected_str,
                    result_str
                );
                free(result_str);
                return E_WRONG_RESULT;
            }
        } else { // ... but we expected null
            printf("\tFAIL: Got a non-null pointer for an unexpected key.\n");
            free(result_str); // Potentially dangerous
            return E_PHANTOM_RESULT;
        }
    } else { // We got a NULL pointer
        if (expected_str) { // ... but we expected a real result
            printf(
                "\tFAIL: Expected '%s' but got a null pointer.\n",
                expected_str
            );
            return E_NULL_GET;
        }
    }
    return E_OK;
}
