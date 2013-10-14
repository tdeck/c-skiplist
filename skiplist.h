/*  A simple C skip list implementation mapping string keys to string values.
 *
 *  Designed with simplicity and minimalism in mind, this implementation uses
 *  fixed-size pillar arrays.
 *
 *  I wrote this because skip lists are my favorite data structure. They are
 *  relatively easy to write and understand (in contrast with certain types of
 *  self-balancing binary trees), use no "magic" hash functions, and still
 *  manage to provide expected O(log n) insertion, search, and deletion.
 *
 *  (C) 2013 by Troy Deck; see LICENSE.txt for details
 */
#ifndef SLIST
#define SLIST   1

// This defines the maximum number of next pointers that can be stored in a
// single node. For good performance, a good rule of thumb is to set this to
// lg(N), where:
//      lg() is the base-2 logarithm function
//      N is the maximum number of entries in your list
//  If you set this to 1, you will get a slightly slower sorted linked list 
//  implementation.
#define MAX_SKIPLIST_HEIGHT     8

typedef struct sl_entry {
    char * key;
    char * value;
    int height;
    struct sl_entry * next[MAX_SKIPLIST_HEIGHT];
} sl_entry;

// Note: All of these functions copy the strings provided to avoid any internal
// dangling pointers. You still own the pointers you pass in, and are 
// responsible for managing that memory. Pointers returned to you point
// to copied values, and you are also responsible for freeing those pointers
// when you no longer need them.
sl_entry * sl_init(); // Allocates a new list and return its head
void sl_destroy(sl_entry * head); // Frees the resources used by a list
char * sl_get(sl_entry * head, char * key); // Returns a key's value
void sl_set(sl_entry * head, char * key, char * value); // Sets a key's value
void sl_unset(sl_entry * head, char * key); // Removes a key, value pair
#endif
