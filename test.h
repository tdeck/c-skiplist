// (C) 2013 by Troy Deck; see LICENSE.txt for details
#include "skiplist.h" 

enum return_codes {
    E_OK = 0,               // Nothing wrong
    E_NULL_INIT = 1,        // An sl_init call failed
    E_NULL_GET = 2,         // An sl_get for a key in the list returned null
    E_WRONG_RESULT = 3,     // A result from sl_get was not as expected
    E_PHANTOM_RESULT = 4    // Some result was returned for an element that
                            // should not have been in the list
};

int main();
int test_get_set();
int test_unset();
int test_hundred_inserts();
int assert_sl_get(sl_entry * head, char * key, char * expected_str);
